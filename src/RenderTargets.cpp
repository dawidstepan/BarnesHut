#include <RenderTargets.hpp>

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iterator>


using CirclePtrVec = std::vector<std::unique_ptr<sf::CircleShape>>;

StateOfCircles::StateOfCircles(std::vector<Body>* stateOfBodies, float circleRadius = 10.f) {
    // Setup initial list of pointers to circle objects in state
    for (auto it = stateOfBodies->begin(); it != stateOfBodies->end(); ++it)
    {
        auto circle = sf::CircleShape(circleRadius);
        auto pos = it->getPos();
        circle.setFillColor(sf::Color::Black);
        circle.setPosition(pos.x, pos.y);
        state.push_back(circle);
    }
}


void StateOfCircles::update_state(std::vector<Body> &stateOfBodies, bool showVelocity = false) {
    auto body_size = stateOfBodies.size();
    // If number of points decreased due to collision detection, remove 
    // remove the excess circles.
    auto size_diff = state.size() - body_size;
    for (int i = 0; i < size_diff; ++i) {
        state.pop_back();
    }

    // Loop over indices of stateOfBodies and transfer information to
    // StateOfCircles.state
    for (int i = 0; i < body_size; i++) {
        auto pos = stateOfBodies[i].getPos();
        state[i].setPosition(pos.x, pos.y);

        if (showVelocity) {
            auto vel = stateOfBodies[i].getVel();
            // Implement magnitude of velocity vector
            // Implement color scale based on magnitude
            state[i].setFillColor(sf::Color::Red);
        }

    }
}


