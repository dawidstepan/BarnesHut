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
// @todo try adding SFML to the conanfile.txt and see if it works
// @todo implement visualization stuff (nothing on that part is included yet)
// @todo implement parseFile in InputHandler
// @todo implement BarnesHut & Naive algorithm
// @todo implement numerical integrator
// @todo eventually implement writeDataToDisc in Writer
// @todo maybe add logging functionality for more convenient debugging
// @todo maybe optimize stateOfBodiesOvertime (we don't need to save methods, only attributes)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

int main(){
    std::vector<Body> currentStateOfBodies;    ///< this vector contains the current state of all our bodies
    std::vector<std::vector<Body>> stateOfBodiesOverTime;
    GeneralParameters generalParameters;

    generalParameters.dt = 1;
    generalParameters.theta = 2222;
    generalParameters.totalNumberOfSteps= 3;

    // just random sample code to show some functions in action
    Vector2D newVector(1, 2);  //that's how we initialize our vector2D Object,
    Body NewBody(100, 1, newVector, newVector, newVector); // similar to the body object
    InputHandler inputHandler(&currentStateOfBodies); // we have to initialize inputHandler with pointer to currentStateOfBodies
    inputHandler.fillStateOdBodiesRandomly(3);
    std::cout << "The third body has the coordinates ("
                << currentStateOfBodies[2].getPos().x
                << ", " << currentStateOfBodies[2].getPos().y  << ")" << std::endl;
    return 0;
}