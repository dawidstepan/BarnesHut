#include <vector>
#include <iostream>

# include "InputHandler.hpp"
# include "Simulation.hpp"
# include "Writer.hpp"
# include "Body.hpp"
# include "GeneralParameters.hpp"
# include "DataPoint.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * To Do-Liste * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// @todo try adding SFML to the conanfile.txt and see if it works (v)
// @todo implement parseFile in InputHandler
// @todo implement BarnesHut algorithm to calculate force
// @todo implement basic collision detection for naive algorithm
// @todo create files for visualizer, update build system so it builds as separate executable
// @todo implement writeDataToDisc in Writer
// @todo figure out how to read binary file from disc
// @todo maybe implement a better integrator (Verlet-integrator)
// @todo maybe add logging functionality for more convenient debugging
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

int main(){

    float theta = 1;    /// describes the quality of our Barnes-Hut approximation
    int dt = 3600;         /// timestep in seconds
    int totalNumberOfSteps = 2000;
    int saveOnEveryXthStep = 1;
    std::string algorithm = "Naive"; 


    std::vector<Body> currentStateOfBodies; 
    InputHandler inputHandler(currentStateOfBodies);

    // Automatic creation of randomly distributed particles:
    // Nico: this does not work with weights smaller than 1 (e.g. 0.5). 
    // Does anyone have an idea why??
    inputHandler.fillStateOfBodiesRandomly(20, 696340, 10., -15, 0.1);
    inputHandler.fillStateOfBodiesRandomly(20, 696340, 10., 15, 0.3);

    Simulation simulation(dt, algorithm, theta);
    simulation.initializeFromVector(currentStateOfBodies);

    for (int i=0; i < totalNumberOfSteps; i++){
        simulation.runStep();
        if (i % saveOnEveryXthStep == 0)
            simulation.saveStep();
    }

    GravityGUI gui(600, "Rescale", {-30.f, 60.f});
    
    auto trajectory = simulation.getStateOfDataPointsOverTime();
    gui.renderTrajectory(trajectory);

    return 0;
}