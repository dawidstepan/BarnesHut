#pragma once

#include <vector>
#include <memory>

#include "Body.hpp"
#include "GeneralParameters.hpp"
#include "DataPoint.hpp"
#include "gui.hpp"
#include "ForceCalculator.hpp"
#include "EulerIntegrator.hpp"

/**
 * includes the core functionality of our program.
 * has to be initialized with a pointer to currentStateOfBodies,
 * a pointer to stateOfBodiesOverTime,
 * and a pointer to generalParameters
 */
class Simulation {
public:
    Simulation(const int dt = 3600, std::string algorithm = "Naive", float theta = 1);

    ///executes the Simulation
    void runStep();

    void saveStep();

    void initializeFromVector (std::vector<Body> StateOfBodies);

    std::vector<std::vector<DataPoint>> getStateOfDataPointsOverTime();

private:
    /// the most basic approach to calculating the force between the objects
    std::vector<Body> currentStateOfBodies;
    std::vector<std::vector<DataPoint>> stateOfBodiesOverTime;
    std::unique_ptr<ForceCalculator> forceCalc;
    std::unique_ptr<EulerIntegrator> integrator;
};
