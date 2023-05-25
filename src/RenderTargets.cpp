#include <RenderTargets.hpp>

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iterator>


float Identity::apply(float value){
    return value;
}

Rescale::Rescale(float min, float max, float new_min, float new_max)
: min(min), new_min(new_min) {
    range = max - min;
    new_range = new_max - new_min;
};

float Rescale::apply(float value) {
    return (((value - min) / range) * new_range) + new_min;
}


// template <typename Transform>
// StateOfCircles::StateOfCircles
// (
//     std::vector<Body> &stateOfBodies, 
//     float circleRadius,
//     Transform transform
// ) : transform(transform)
// {
//     // Setup initial list of pointers to circle objects in state
//     for (auto it = stateOfBodies.begin(); it != stateOfBodies.end(); ++it)
//     {
//         auto circle = sf::CircleShape(circleRadius);
//         auto pos = it->getPos();
//         circle.setFillColor(sf::Color::Green);
//         circle.setPosition(pos.x, pos.y);
//         state.push_back(circle);
//     }
// }

template <typename Transform>
StateOfCircles<Transform>::StateOfCircles
(
    std::vector<DataPoint> &stateOfDataPoints, 
    Transform transform,
    float circleRadius
) : transform(transform)
{
    // Setup initial list of pointers to circle objects in state
    for (auto it = stateOfDataPoints.begin(); it != stateOfDataPoints.end(); ++it)
    {
        auto circle = sf::CircleShape(circleRadius);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(
            transform.apply(it->x), 
            transform.apply(it->y)
        );
        state.push_back(circle);
    }
}


// template <typename Transform>
// void StateOfCircles<Transform>::update_state_from_bodies
// (
//     std::vector<Body> &stateOfBodies, 
//     bool showVelocity
// )
// {
//     auto body_size = stateOfBodies.size();
//     // If number of points decreased due to collision detection, remove 
//     // remove the excess circles.
//     auto size_diff = state.size() - body_size;
//     for (int i = 0; i < size_diff; ++i) 
//     {
//         state.pop_back();
//     }

//     // Loop over indices of stateOfBodies and transfer information to
//     // StateOfCircles.state
//     for (int i = 0; i < body_size; i++) 
//     {
//         auto pos = stateOfBodies[i].getPos();
//         state[i].setPosition(pos.x, pos.y);

//         if (showVelocity) 
//         {
//             auto vel = stateOfBodies[i].getVel();
//             // Implement magnitude of velocity vector
//             // Implement color scale based on magnitude
//             state[i].setFillColor(sf::Color::Red);
//         }

//     }
// }

template <typename Transform>
void StateOfCircles<Transform>::update_state_from_data_points
(
    std::vector<DataPoint> &stateOfDataPoints, 
    bool showVelocity
) 
{
    auto body_size = stateOfDataPoints.size();
    // If number of points decreased due to collision detection, remove 
    // remove the excess circles.
    auto size_diff = state.size() - body_size;
    for (int i = 0; i < size_diff; ++i) {
        state.pop_back();
    }

    // Loop over indices of stateOfBodies and transfer information to
    // StateOfCircles.state
    for (int i = 0; i < body_size; i++) {
        auto point = stateOfDataPoints[i];
        state[i].setPosition(
            transform.apply(point.x), 
            transform.apply(point.y)
        );

        if (showVelocity) {
            // auto vel = stateOfBodies[i].getVel();
            auto vx = point.vx;
            // Implement magnitude of velocity vector
            // Implement color scale based on magnitude
            state[i].setFillColor(sf::Color::Red);
        }

    }
}

template struct StateOfCircles<Identity>;
template struct StateOfCircles<Rescale>;
