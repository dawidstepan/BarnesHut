#include <gui.hpp>
#include <RenderTargets.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>


GravityGUI::GravityGUI(int width)
    : window(sf::VideoMode(width, width), "Gravity Simulator") {};

void GravityGUI::renderTrajectory
(
    std::vector<std::vector<DataPoint>> &stateOfDataPointsOverTime
) 
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 20.f);
    
    auto transform = Rescale(0, 10, 0, window.getSize().x);
    auto state = StateOfCircles<Rescale>(stateOfDataPointsOverTime[0], transform);

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
    
    auto transform = Rescale(0, 10, 0, window.getSize().x);
    auto state = StateOfCircles<Rescale>(stateOfDataPoints, transform);

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