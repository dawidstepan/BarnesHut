#include <gui.hpp>
#include <InputHandler.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <unistd.h>
#include <stdexcept>
#include <cmath>


GravityGUI::GravityGUI(int width, std::string transform, std::vector<float> range, 
                       int print_fps_every)
: window(sf::VideoMode(width, width), "Gravity Simulator"), print_fps_every(print_fps_every)
{   
    if (transform == "Rescale") 
    {
        transformation = std::make_shared<Rescale>(range[0], range[1], 0, window.getSize().x);
    }
    else if (transform == "Identity")
    {
        transformation = std::make_shared<Identity>();
    }
    else
    {
      throw std::runtime_error("Unknown transformation! Supported are 'Rescale' and 'Identity'");
    }
};


void GravityGUI::renderTrajectory
(
    std::vector<std::vector<DataPoint>> &stateOfDataPointsOverTime
) 
{
    window.setFramerateLimit(60);

    sf::Clock clock;
    
    ProgressBar progressbar(window);
    FPSDisplay fps_display(window);
    auto pause_pos = sf::Vector2f(0.7 * window.getSize().x, 0.1 * window.getSize().y);
    Button pauseButton(pause_pos, "Resume", "Pause", window);

    auto color_scale = std::make_unique<ColorScale>(0, 0.2, sf::Color::Blue, sf::Color::White);
    // auto color_scale = std::make_unique<ColorScale>(0, 1000000, sf::Color::Blue, sf::Color::White);
    auto state = StateOfCircles(stateOfDataPointsOverTime[0], 
                                std::move(transformation), 
                                std::move(color_scale), 
                                2.f);
    auto total_frame_number = stateOfDataPointsOverTime.size();
    
    bool paused = false;
    int frame_index = 0;
    float time_fps = 0;
    float print_fps = 0;
    auto it = stateOfDataPointsOverTime.begin();
    auto end = stateOfDataPointsOverTime.end();
    while (window.isOpen()) 
    {   

        while (true) {
            pauseButton.draw();
            while (true) {
                // reset iterator if at end -> infinite loop
                if (it == end)
                    it = stateOfDataPointsOverTime.begin();
                auto time_step = *it;

                // Draw a Pause button which upon clicking pauses the animation
                window.clear();
                pauseButton.draw();
                state.update_state_from_data_points(time_step, true);

                for (auto target : state.state) {
                    window.draw(target);
                }
                sf::Time time = clock.getElapsedTime();
                clock.restart().asSeconds();

                // Draw the FPS averaged over the last print_fps_every iterations
                time_fps += time.asSeconds();
                if (frame_index % print_fps_every == 0)
                {
                    print_fps = static_cast<int>(1.f * print_fps_every / time_fps);
                    time_fps = 0;
                }
                fps_display.draw(print_fps);



                float progress;
                if (!pauseButton.isPressed())
                {
                    // Draw a progress bar showing the progress of the animation
                    progress = static_cast<float>(frame_index) / total_frame_number;
                    it++;
                    frame_index++;
                }

                progressbar.draw(std::fmod(progress, 1.f));
                
                window.display();

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    // else if (event.type == sf::Event::MouseButtonPressed)
                    //     window.setFramerateLimit(60);

                    pauseButton.handleEvent(event);
                }
            }

        }

    }
}

void GravityGUI::renderSnapshot(std::vector<DataPoint> &stateOfDataPoints) {

    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 20.f);
    
    auto color_scale = std::make_unique<ColorScale>(0, 10);
    auto state = StateOfCircles(stateOfDataPoints, 
                                std::move(transformation), 
                                std::move(color_scale), 
                                2.f);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (auto target : state.state) {
            window.draw(target);
        }
        sleep(0.1);
        window.display();
    
    }
}




void GravityGUI::renderSimulation
(
    Simulation &simulation
) 
{
    sf::Clock clock;
    ProgressBar progressbar(window);
    FPSDisplay fps_display(window);
    auto pause_pos = sf::Vector2f(0.7 * window.getSize().x, 0.1 * window.getSize().y);
    Button pauseButton(pause_pos, "Resume", "Pause", window);
    auto draw_pos = sf::Vector2f(0.7 * window.getSize().x, 0.2 * window.getSize().y);
    Button drawButton(draw_pos, "Deactivate", "Activate", window);

    auto color_scale = std::make_unique<ColorScale>(0, 0.2, sf::Color::Blue, sf::Color::White);
    auto initialStateOfBodies = simulation.getCurrentStateOfBodies();
    auto state = StateOfCircles(initialStateOfBodies, 
                                transformation, 
                                std::move(color_scale), 
                                2.f);
    std::vector<Body> time_step;
    sf::Vector2i mousePosition;

    bool paused = false;
    bool shutdown = false;
    bool add_particles = false;
    int frame_index = 0;
    float time_fps = 0;
    float print_fps = 0;

    while (window.isOpen()) 
    {   

        while (!shutdown) {
            pauseButton.draw();
            drawButton.draw();
            while (!shutdown) {

                // Compute the timestep
                if (!pauseButton.isPressed())
                {
                    simulation.runStep();
                    time_step = simulation.getCurrentStateOfBodies();
                    frame_index++;
                }

                // dynamically add particles
                if (drawButton.isPressed() & add_particles)
                {
                    time_step = simulation.getCurrentStateOfBodies();
                    InputHandler inputHandler(time_step);
                    auto spawn_x = transformation->reverse(mousePosition.x);
                    auto spawn_y = transformation->reverse(mousePosition.y);
                    inputHandler.fillStateOfBodiesRandomly(10, 696340, 100, Vector2D(spawn_x, spawn_y), Vector2D(10,10));
                    simulation.initializeFromVector(time_step);
                }

                // Draw a Pause button which upon clicking pauses the animation
                window.clear();
                pauseButton.draw();
                drawButton.draw();
                state.update_state_from_bodies(time_step, true);

                for (auto target : state.state) {
                    window.draw(target);
                }
                sf::Time time = clock.getElapsedTime();
                clock.restart().asSeconds();

                // Draw the FPS averaged over the last print_fps_every iterations
                time_fps += time.asSeconds();
                if (frame_index % print_fps_every == 0)
                {
                    print_fps = static_cast<int>(1.f * print_fps_every / time_fps);
                    time_fps = 0;
                }
                fps_display.draw(print_fps);

                window.display();
                add_particles = false;

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        {
                            window.close();
                            shutdown = true;
                        }
                    else if (event.type == sf::Event::MouseWheelScrolled)
                        add_particles = true;
                        mousePosition = sf::Mouse::getPosition(window);

                    pauseButton.handleEvent(event);
                    drawButton.handleEvent(event);
                }
            }
        }
    }
}