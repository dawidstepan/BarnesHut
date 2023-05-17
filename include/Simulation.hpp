#ifndef GROUPMPROJECT_SIMULATION_HPP
#define GROUPMPROJECT_SIMULATION_HPP

#include <vector>
#include "Body.hpp"
#include "GeneralParameters.hpp"


class Simulation {
public:
    Simulation(std::vector<Body> *stateOfBodies,
               std::vector<std::vector<Body>> *stateOfBodiesOverTime,
               const GeneralParameters *generalParameters) :
            stateOfBodies(stateOfBodies),
            stateOfBodiesOverTime(stateOfBodiesOverTime),
            generalParameters(generalParameters) {};

    void updateStateOfBodiesOverTime(std::vector<Body> currentState);


    void runSimulation(int dt, int totalNumberOfSteps, int saveOnEveryXthStep, std::vector<Body> currentStateOfBodies, int algorithmToUse);


private:
    std::vector<Body> *stateOfBodies;
    std::vector<std::vector<Body>> *stateOfBodiesOverTime;
    const GeneralParameters *generalParameters;
    float theta;
    int dt;
    int totalNumberOfSteps;
};


#endif //GROUPMPROJECT_SIMULATION_HPP
