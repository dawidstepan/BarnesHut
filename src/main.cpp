#include <vector>

# include "InputHandler.hpp"
# include "Simulation.hpp"
# include "Writer.hpp"
# include "Body.hpp"
# include "GeneralParameters.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * To Do-Liste * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// @todo try adding SFML to the conanfile.txt and see if it works
// @todo implement visualization stuff (nothing on that part is included yet)
// @todo implement parseFile in InputHandler
// @todo implement BarnesHut algorithm
// @todo implement collision detection
// @todo eventually implement writeDataToDisc in Writer
// @todo maybe implement a better integrator (Verlet-integrator)
// @todo maybe add logging functionality for more convenient debugging
// @todo maybe optimize stateOfBodiesOvertime (we don't need to save methods, only attributes)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

int main(){
    std::vector<Body> currentStateOfBodies;    ///< this vector contains the current state of all our bodies
    std::vector<std::vector<Body>> stateOfBodiesOverTime;
    GeneralParameters generalParameters;

    generalParameters.dt = 3600;   //dt in seconds
    generalParameters.theta = 1;
    generalParameters.totalNumberOfSteps=25;
    generalParameters.saveOnEveryXthStep=1;
    generalParameters.algorithmToUse=0;

    // random sample code to show some functions in action
    /*
     * x- & y coordinates in astronomical Units,
     * weight in sun masses
     */
    Vector2D initialPos1(0, -5);
    Vector2D initialPos2(0, 5);
    Vector2D nullVector(0, 0);

    InputHandler inputHandler(&currentStateOfBodies);
    inputHandler.addToStateOfBodies(6e3, 1, initialPos1, nullVector, nullVector);
    inputHandler.addToStateOfBodies(6e3, 1, initialPos2, nullVector, nullVector);


    Simulation simulation(&currentStateOfBodies, &stateOfBodiesOverTime, &generalParameters);
    simulation.runSimulation();


    return 0;
}