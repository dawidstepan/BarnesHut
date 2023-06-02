#pragma once

#include <vector>
#include <memory>

#include "Body.hpp"
#include "GeneralParameters.hpp"
#include "DataPoint.hpp"
#include "gui.hpp"
#include "ForceCalculator.hpp"

/**
 * includes the core functionality of our program.
 * has to be initialized with a pointer to currentStateOfBodies,
 * a pointer to stateOfBodiesOverTime,
 * and a pointer to generalParameters
 */
class Simulation {
public:
    Simulation(std::vector<Body> &currentStateOfBodies,
               std::vector<std::vector<DataPoint>> &stateOfBodiesOverTime,
               const GeneralParameters &generalParameters);


    ///executes the Simulation
    void runSimulation();
    // void runSimulation(GravityGUI &GUI);

private:
    /// the most basic approach to calculating the force between the objects
    std::vector<Body> &currentStateOfBodies;
    std::vector<std::vector<DataPoint>> &stateOfBodiesOverTime;
    const GeneralParameters &generalParameters;
    std::unique_ptr<ForceCalculator> ForceCalc;
};

// class Simulation {
// public:
//     Simulation(std::vector<Body> &currentStateOfBodies,
//                std::vector<std::vector<DataPoint>> &stateOfBodiesOverTime,
//                const GeneralParameters &generalParameters) :
//             currentStateOfBodies(currentStateOfBodies),
//             stateOfBodiesOverTime(stateOfBodiesOverTime),
//             generalParameters(generalParameters) {};


//     ///executes the Simulation
//     void runSimulation();
//     // void runSimulation(GravityGUI &GUI);

// private:
//     /// the most basic approach to calculating the force between the objects
//     Vector2D getForceByNaiveAlgorithm(std::vector<Body>, std::vector<Body>::iterator iteratorToBody);

//     /// more sophisticated way of approximating the force
//     Vector2D getForceByBarnesHutAlgorithm(std::vector<Body>, std::vector<Body>::iterator iteratorToBody);

//     std::vector<Body> &currentStateOfBodies;
//     std::vector<std::vector<DataPoint>> &stateOfBodiesOverTime;
//     const GeneralParameters &generalParameters;
// };

