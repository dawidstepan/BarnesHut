#ifndef GROUPMPROJECT_SIMULATION_HPP
#define GROUPMPROJECT_SIMULATION_HPP

#include <vector>
#include "Body.hpp"
#include "GeneralParameters.hpp"

/**
 * includes the core functionality of our programm.
 * has to be initiaized with a pointer to currentStateOfBodies,
 * a pointer to stateOfBodiesOverTime,
 * and a pointer to generalParameters
 */
class Simulation {
public:
    Simulation(std::vector<Body> *currentStateOfBodies,
               std::vector<std::vector<Body>> *stateOfBodiesOverTime,
               const GeneralParameters *generalParameters) :
            currentStateOfBodies(currentStateOfBodies),
            stateOfBodiesOverTime(stateOfBodiesOverTime),
            generalParameters(generalParameters) {};
    ///executes the Simulation
    void runSimulation();

private:
    void updateStateOfBodiesOverTime(std::vector<Body> currentState);

    Vector2D getForceByNaiveAlgorithm(std::vector<Body>*, std::vector<Body>::iterator iteratorToBody);

    /// the most basic approach to calculating the force between the objects
    Vector2D getForceByBarnesHutAlgorithm(std::vector<Body>*, std::vector<Body>::iterator iteratorToBody);


    std::vector<Body> *currentStateOfBodies;
    std::vector<std::vector<Body>> *stateOfBodiesOverTime;

    const GeneralParameters *generalParameters;
};


#endif //GROUPMPROJECT_SIMULATION_HPP
