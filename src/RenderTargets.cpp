#include <RenderTargets.hpp>

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iterator>
#include <cmath>


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


ColorScale::ColorScale(float minValue, float maxValue, sf::Color color1, sf::Color color2)
: minValue(minValue), maxValue(maxValue), color1(color1), color2(color2)
{

}

sf::Color ColorScale::interpolateColor(sf::Color color1, sf::Color color2, float t) {
    sf::Uint8 r = static_cast<sf::Uint8>((1.f - t) * color1.r + t * color2.r);
    sf::Uint8 g = static_cast<sf::Uint8>((1.f - t) * color1.g + t * color2.g);
    sf::Uint8 b = static_cast<sf::Uint8>((1.f - t) * color1.b + t * color2.b);
    return sf::Color(r, g, b);
}

sf::Color ColorScale::getColorFromValue(float value) {
    if (value > maxValue)
        value = maxValue;

    // Normalize the value to the range [0, 1]
    float normalizedValue = (value - minValue) / (maxValue - minValue);

    // Interpolate between the two colors based on the normalized value
    return interpolateColor(color1, color2, normalizedValue);
}


StateOfCircles::StateOfCircles
(
    std::vector<DataPoint> &stateOfDataPoints, 
    std::unique_ptr<Transformation> trafo,
    std::unique_ptr<ColorScale> scale,
    float circleRadius
) : transform(std::move(trafo)), color_scale(std::move(scale))
{
    // Setup initial list of pointers to circle objects in state
    for (auto it = stateOfDataPoints.begin(); it != stateOfDataPoints.end(); ++it)
    {
        auto circle = sf::CircleShape(circleRadius);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(
            transform->apply(it->x), 
            transform->apply(it->y)
        );
        state.push_back(circle);
    }
}


void StateOfCircles::update_state_from_data_points
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
            transform->apply(point.x), 
            transform->apply(point.y)
        );

        if (showVelocity) {
            auto v_mag = std::sqrt(point.ax*point.ax + point.ay*point.ay);
            // auto v_mag = std::sqrt(point.vx*point.vx + point.vy*point.vy);
            state[i].setFillColor(color_scale->getColorFromValue(v_mag));
        }

    }
}