// #pragma once
// #ifndef GROUPMPROJECT_RENDERTARGETS_HPP
// #define GROUPMPROJECT_RENDERTARGETS_HPP


#include <Body.hpp>
#include <DataPoint.hpp>

#include <SFML/Graphics.hpp>
#include <vector>


struct StateOfCircles {

public:
    std::vector<sf::CircleShape> state;

    StateOfCircles(std::vector<Body>* stateOfBodies, float circleRadius);
    StateOfCircles(std::vector<DataPoint> &stateOfDataPoints, float circleRadius);
    
    void update_state_from_bodies(std::vector<Body> &stateOfBodies, bool showVelocity);
    void update_state_from_data_points(std::vector<DataPoint> &stateOfDataPoints, bool showVelocity);

};



// #endif // GROUPMPROJECT_RENDERTARGETS_HPP
