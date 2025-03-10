#include <vector>
#include <iostream>

#include "InputHandler.hpp"
#include "Simulation.hpp"
#include "gui.hpp"
#include "Writer.hpp"
#include "Body.hpp"
#include "DataPoint.hpp"


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

    float theta = 0.75;    /// describes the quality of our Barnes-Hut approximation
    int dt = 3600;         /// timestep in seconds
    int totalNumberOfSteps = 200;
    int saveOnEveryXthStep = 10;
    std::string algorithm = "BarnesHut"; 
    std::string usedIntegrator = "verlet";
    bool showLive = true;

    std::vector<Body> currentStateOfBodies; 
    InputHandler inputHandler(currentStateOfBodies);

    inputHandler.fillStateOfBodiesRandomly(200, 696340, 0.5, Vector2D(0, 0), Vector2D(100, 100));
    inputHandler.fillStateOfBodiesRandomly(1, 696340, 100000, Vector2D(50, 50), Vector2D(10, 10));

    Simulation simulation(dt, algorithm, usedIntegrator, theta);
    simulation.initializeFromVector(currentStateOfBodies);

    if (showLive)
    {
        GravityGUI gui(600, "Rescale", {-100.f, 200.f});
        gui.renderSimulation(simulation);
    }
    else
    {
        for (int i=0; i < totalNumberOfSteps; i++){
            simulation.runStep();
            if (i % saveOnEveryXthStep == 0)
                simulation.saveStep();
        }

        GravityGUI gui(600, "Rescale", {-200.f, 500.f});
        
        auto trajectory = simulation.getStateOfDataPointsOverTime();
        gui.renderTrajectory(trajectory);
    }
    
    return 0;
}