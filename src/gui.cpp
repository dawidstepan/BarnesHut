#include <gui.hpp>
#include <RenderTargets.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <unistd.h>
#include <stdexcept>


GravityGUI::GravityGUI(int width, std::string transform, std::vector<float> range)
: window(sf::VideoMode(width, width), "Gravity Simulator") 
{
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
    sf::Time timeSinceLastFrame = sf::Time::Zero;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 20.f);
    
    auto state = StateOfCircles(stateOfDataPointsOverTime[0], std::move(transformation), 10.f);

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
            // sleep(0.5);
            window.display();
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