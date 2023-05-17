#include <iostream>
#include <vector>
//----Custom Includes-----
# include "InputHandler.hpp"
# include "Simulation.hpp"
# include "Writer.hpp"
# include "Body.hpp"
# include "GeneralParameters.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * To Do-Liste * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// @todo finish runSim method
// @todo change data type in Vector2D (see warnings)
// @todo try adding SFML to the conanfile.txt and see if it works
// @todo implement parseFile in InputHandler
// @todo implement BarnesHut & Naive algorithm
// @todo implement numerical integrator
// @todo eventually implement fillStateOdBodiesRandomly in InputHandler
// @todo eventually implement writeDataToDisc in Writer
// @todo maybe add logging functionality for more convenient debuging
// @todo maybe optimize stateOfBodiesOvertime (we don't need to save methods, only attributes)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

int main(){
    std::vector<Body> currentStateOfBodies;    ///< this vector contains the current state of all our bodies
    std::vector<std::vector<Body>> stateOfBodiesOverTime;
    GeneralParameters generalParameters;

    generalParameters.dt = 1;
    generalParameters.theta = 2222;
    generalParameters.totalNumberOfSteps= 3;

    // just sample code to show some functions in action
    Vector2D newVector(123, 456);
    Body NewBody(100, 1, newVector, newVector, newVector);
    InputHandler inputHandler(&currentStateOfBodies);
    currentStateOfBodies.push_back(NewBody);
    inputHandler.addToStateOfBodies(1, 2, newVector, newVector, newVector);
    std::cout << currentStateOfBodies[1].getSize() << std::endl;
    return 0;
}