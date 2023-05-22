// #pragma once
// #ifndef GROUPMPROJECT_RENDERTARGETS_HPP
// #define GROUPMPROJECT_RENDERTARGETS_HPP

#include <Body.hpp>

#include <SFML/Graphics.hpp>
#include <vector>


struct StateOfCircles {

private:
     std::vector<sf::CircleShape> state;

public:

    StateOfCircles(std::vector<Body>* stateOfBodies, float circleRadius);
    
    void update_state(std::vector<Body> &stateOfBodies, bool showVelocity);

};



// #endif // GROUPMPROJECT_RENDERTARGETS_HPP
