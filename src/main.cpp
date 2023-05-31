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

    std::vector<Body> currentStateOfBodies;    ///< this vector contains the current state of all our bodies
    std::vector<std::vector<DataPoint>> stateOfDataPointsOverTime; ///< contains a stripped-down copy of currentStateOfBodies for each timestep
    GeneralParameters generalParameters{};

    generalParameters.dt = 3600;   //dt in seconds
    generalParameters.theta = 1;
    generalParameters.totalNumberOfSteps=1000;
    generalParameters.saveOnEveryXthStep=1;
    generalParameters.algorithmToUse=0;

    // random sample code to show some functions in action
    /*
     * x- & y coordinates in astronomical Units,
     * weight in sun masses
     */

    InputHandler inputHandler(currentStateOfBodies);

    // Manual creation of StateOfBodies:
    // Vector2D initialPos1(0, 7);
    // Vector2D initialPos2(0, 5);
    // Vector2D nullVector(0, 0);
    // inputHandler.addToStateOfBodies(6e3, 1, initialPos1, nullVector, nullVector);
    // inputHandler.addToStateOfBodies(6e3, 1, initialPos2, nullVector, nullVector);
    
    // Automatic creation of randomly distributed particles:
    // Nico: this does not work with weights smaller than 1 (e.g. 0.5). 
    // Does anyone have an idea why??
    inputHandler.fillStateOfBodiesRandomly(100, 696340, 1.);

    Simulation simulation(currentStateOfBodies, stateOfDataPointsOverTime, generalParameters);
    simulation.runSimulation();

    GravityGUI gui(600, "Rescale", {-10.f, 10.f});
    
    // gui.renderSnapshot(stateOfDataPointsOverTime[0]);
    gui.renderTrajectory(stateOfDataPointsOverTime);

    return 0;
}