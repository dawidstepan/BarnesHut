#pragma once
// #ifndef GROUPMPROJECT_RENDERTARGETS_HPP
// #define GROUPMPROJECT_RENDERTARGETS_HPP


#include <Body.hpp>
#include <DataPoint.hpp>

#include <SFML/Graphics.hpp>
#include <vector>

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



/************************************************
 * Creates container 'state' for the sf::CircleShape objects which have to be 
 * rendered in the SFML window. Contains convenience methods to create and update 
 * the state from a std::vector<DataPoint> container.
 * 
 * Disclaimer:
 * This works so far for a single snapshot, but fails for a "trajectory" of 
 * snapshots, which should be the final goal to create an animation..
 ***********************************************/
template <typename Transform>
struct StateOfCircles {

public:
    std::vector<sf::CircleShape> state;
    Transform transform;

    // StateOfCircles
    // (
    //     std::vector<Body> &stateOfBodies, 
    //     float circleRadius = 10.f,
    //     Transform transform = Identity()
    // );


    /************************************************
     * Constructor to create a StateOfCircles object from std::vector<DataPoint>
     ***********************************************/
    StateOfCircles
    (
        std::vector<DataPoint> &stateOfDataPoints, 
        Transform transform,
        float circleRadius = 10.f
    );
    

    // void update_state_from_bodies
    // (
    //     std::vector<Body> &stateOfBodies,
    //     bool showVelocity = false
    // );

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


// #endif // GROUPMPROJECT_RENDERTARGETS_HPP
