#ifndef GROUPMPROJECT_SIMULATION_HPP
#define GROUPMPROJECT_SIMULATION_HPP

#include <vector>
#include "Body.hpp"
#include "GeneralParameters.hpp"
#include "DataPoint.hpp"

/**
 * includes the core functionality of our program.
 * has to be initialized with a pointer to currentStateOfBodies,
 * a pointer to stateOfBodiesOverTime,
 * and a pointer to generalParameters
 */
class Simulation {
public:
    Simulation(std::vector<Body> *currentStateOfBodies,
               std::vector<std::vector<DataPoint>> *stateOfBodiesOverTime,
               const GeneralParameters *generalParameters) :
            currentStateOfBodies(currentStateOfBodies),
            stateOfBodiesOverTime(stateOfBodiesOverTime),
            generalParameters(generalParameters) {};


    ///executes the Simulation
    void runSimulation();

private:
    void updateStateOfBodiesOverTime(std::vector<DataPoint> currentStateOfDataPoints);

    /// the most basic approach to calculating the force between the objects
    Vector2D getForceByNaiveAlgorithm(std::vector<Body>*, std::vector<Body>::iterator iteratorToBody);

    /// more sophisticated way of approximating the force
    Vector2D getForceByBarnesHutAlgorithm(std::vector<Body>*, std::vector<Body>::iterator iteratorToBody);

    

    std::vector<Body> *currentStateOfBodies;
    std::vector<std::vector<DataPoint>> *stateOfBodiesOverTime;
    const GeneralParameters *generalParameters;
};


#endif //GROUPMPROJECT_SIMULATION_HPP
