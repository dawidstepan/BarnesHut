#include <gui.hpp>
#include <RenderTargets.hpp>
#include <Widgets.hpp>

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
    // window.setFramerateLimit(5);

    if (transform == "Rescale") 
    {
        transformation = std::make_unique<Rescale>(range[0], range[1], 0, window.getSize().x);
    }
    else if (transform == "Identity")
    {
        transformation = std::make_unique<Identity>();
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
    sf::Clock clock;
    
    ProgressBar progressbar(window);
    FPSDisplay fps_display(window);
    auto pause_pos = sf::Vector2f(0.7 * window.getSize().x, 0.1 * window.getSize().y);
    Button pauseButton(pause_pos, "Resume", "Pause", window);

    auto state = StateOfCircles(stateOfDataPointsOverTime[0], std::move(transformation), 2.f);
    auto total_frame_number = stateOfDataPointsOverTime.size();
    
    bool paused = false;
    int frame_index = 0;
    float time_fps = 0;
    float print_fps = 0;
    while (window.isOpen()) 
    {

        for (auto time_step : stateOfDataPointsOverTime) 
        {   
            // Draw a Pause button which upon clicking pauses the animation
            window.clear();
            pauseButton.draw();
            state.update_state_from_data_points(time_step, false);
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

            // Draw a progress bar showing the progress of the animation
            float progress = static_cast<float>(frame_index) / total_frame_number;
            progressbar.draw(std::fmod(progress, 1.f));

            window.display();
            frame_index++;

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                pauseButton.handleEvent(event);
            }
        }

    }
}

void GravityGUI::renderSnapshot(std::vector<DataPoint> &stateOfDataPoints) {

    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 20.f);
    
    auto state = StateOfCircles(stateOfDataPoints, std::move(transformation), 10.f);

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