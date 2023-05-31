#include <gui.hpp>
#include <RenderTargets.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <unistd.h>
#include <stdexcept>
#include <cmath>


GravityGUI::GravityGUI(int width, std::string transform, std::vector<float> range)
: window(sf::VideoMode(width, width), "Gravity Simulator") 
{   
    window.setFramerateLimit(60);

    init_text();

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

void GravityGUI::init_text()
{
    font.loadFromFile("../assets/DejaVuSerif.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setPosition(sf::Vector2f(10.f, 10.f));
}

void GravityGUI::print_fps(float frames_per_second)
{  
    std::string str = "FPS: " + std::to_string(frames_per_second);
    text.setString(str);
    window.draw(text);
}

void GravityGUI::renderTrajectory
(
    std::vector<std::vector<DataPoint>> &stateOfDataPointsOverTime
) 
{
    sf::Clock clock;
    
    ProgressBar progressbar(window);
    auto state = StateOfCircles(stateOfDataPointsOverTime[0], std::move(transformation), 10.f);
    auto total_frame_number = stateOfDataPointsOverTime.size();

    int frame_index = 0;
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (auto time_step : stateOfDataPointsOverTime) 
        {
            state.update_state_from_data_points(time_step, false);
            window.clear();
            for (auto target : state.state) {
                window.draw(target);
            }
            sf::Time time = clock.getElapsedTime();

            clock.restart().asSeconds();

            print_fps(1.f / time.asSeconds());
            float progress = static_cast<float>(frame_index) / total_frame_number;
            progressbar.draw(window, std::fmod(progress, 1.f));

            window.display();
            frame_index++;
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


ProgressBar::ProgressBar(sf::RenderWindow &window)
{   
    bar_width = 0.8 * window.getSize().x;
    bar_height = 10.f;
    sf::Vector2f barsize(bar_width, bar_height);
    outer_hull.setSize(barsize);
    outer_hull.setFillColor(sf::Color::White);
    outer_hull.setOutlineColor(sf::Color::Blue);
    outer_hull.setOutlineThickness(2.f);
    auto outer_pos = sf::Vector2f(0.1 * window.getSize().x, 0.9 * window.getSize().y);
    outer_hull.setPosition(outer_pos);

    progress_bar.setPosition(outer_pos);
    progress_bar.setFillColor(sf::Color::Blue);
}

void ProgressBar::draw(sf::RenderWindow &window, float progress)
{   
    progress_bar.setSize(sf::Vector2f(progress * bar_width, bar_height));
    window.draw(outer_hull);
    window.draw(progress_bar);
}


// void GravityGUI::renderFromFile
// (
//     std::vector<std::vector<DataPoint>>& stateOfDataPointsOverTime
// )
// {
//     sf::Clock clock;
//     sf::Time timeSinceLastFrame = sf::Time::Zero;
//     const sf::Time TIME_PER_FRAME = sf::seconds(1.f);

//     auto transform = Rescale(0, 10, 0, window.getSize().x);
//     auto state = StateOfCircles<Rescale>(stateOfDataPointsOverTime[0], transform);

//     // Track the current index of the stateOfDataPointsOverTime vector
//     std::size_t currentIndex = 0;

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         timeSinceLastFrame += clock.restart();

//         if (currentIndex < stateOfDataPointsOverTime.size())
//         {
//             // Update the state and render the current data points
//             state.update_state_from_data_points(stateOfDataPointsOverTime[currentIndex], false);
//             window.clear();
//             for (const auto& target : state.state) {
//                 window.draw(target);
//             }
//             window.display();

//             if (timeSinceLastFrame >= TIME_PER_FRAME)
//             {
//                 // Move to the next data points after a certain time
//                 timeSinceLastFrame -= TIME_PER_FRAME;
//                 currentIndex++;
//             }
//         }
//     }
// }