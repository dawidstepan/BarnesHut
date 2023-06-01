#pragma once
// #ifndef GROUPMPROJECT_RENDERTARGETS_HPP
// #define GROUPMPROJECT_RENDERTARGETS_HPP


#include <Body.hpp>
#include <DataPoint.hpp>

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

/************************************************
 * ABC for transformations of a single value.
 ***********************************************/
struct Transformation {
    virtual float apply(float value) = 0;
    
    virtual ~Transformation(){}
};


/************************************************
 * Identity transformation, transforming a value to itself.
 ***********************************************/
struct Identity : public Transformation {
    float apply(float value) override;
};


/************************************************
 * Linear rescaling transformation of a single value from a range (min, max)
 * to a new range (new_min, new_max). This is necessary to rescale the x and y
 * positions of each Body to the range of the SFML window (e.g. 600 * 600)
 ***********************************************/
struct Rescale : public Transformation {

public:
    Rescale(float min, float max, float new_min, float new_max);

    float apply(float value) override;

private:
    float range;
    float new_range;
    float min;
    float new_min;
};

struct ColorScale {

ColorScale(float minValue, float maxValue, 
            sf::Color color1 = sf::Color(59, 76, 192), // blue
            sf::Color color2 = sf::Color(180, 4, 38)); // red

public:

    sf::Color interpolateColor(sf::Color color1, sf::Color color2, float t);

    sf::Color getColorFromValue(float value);

private:
    float minValue;
    float maxValue;
    sf::Color color1;
    sf::Color color2;

};


/************************************************
 * Creates container 'state' for the sf::CircleShape objects which have to be 
 * rendered in the SFML window. Contains convenience methods to create and update 
 * the state from a std::vector<DataPoint> container.
 * 
 * Disclaimer:
 * This works so far for a single snapshot, but fails for a "trajectory" of 
 * snapshots, which should be the final goal to create an animation..
 ***********************************************/
struct StateOfCircles {

public:
    std::vector<sf::CircleShape> state;
    std::unique_ptr<Transformation> transform;
    std::unique_ptr<ColorScale> color_scale;

    /************************************************
     * Constructor to create a StateOfCircles object from std::vector<DataPoint>
     ***********************************************/
    StateOfCircles
    (
        std::vector<DataPoint> &stateOfDataPoints, 
        std::unique_ptr<Transformation> trafo,
        std::unique_ptr<ColorScale> scale,
        float circleRadius = 10.f
    );
    

    /************************************************
     * Updates the positions of the sf::CircleShape instances contained in the
     * state vector.
     ***********************************************/
    void update_state_from_data_points
    (
        std::vector<DataPoint> &stateOfDataPoints, 
        bool showVelocity = false
    );

};