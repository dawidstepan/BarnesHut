#include <string>
#include "Simulation.hpp"
#include "BarnesHutAlgorithm.hpp"
#include "NaiveAlgorithm.hpp"
#include "Integrator.hpp"

void Simulation::updateStateOfBodiesOverTime(std::vector<Body> currentStateOfBodies) {
    stateOfBodiesOverTime -> push_back(currentStateOfBodies);
};

//* * * * * * * * * * *
//UNDER CONSTRUCTION  *
//* * * * * * * * * * *
void Simulation::runSimulation(int dt, int totalNumberOfSteps, int saveOnEveryXthStep,  std::vector<Body> currentStateOfBodies, int algorithmToUse) {
    NaiveAlgorithm naiveAlgorithm;
    BarnesHutAlgorithm barnesHutAlgorithm;
    Integrator integrator;

    for (int i=0; i < totalNumberOfSteps; i++){
        if (i % saveOnEveryXthStep == 0){
            updateStateOfBodiesOverTime(currentStateOfBodies);
        };
        std::vector<Vector2D> forceVectorVector;    //< the i-th index represents the force acting on the i-th body in currentStateOfBodies
        std::vector<Vector2D> deltaAccVectorVector; //< the i-th index represents the change in the acceleration of the i-th body in currentStateOfBodies
        std::vector<Vector2D> deltaVelVectorVector; //< the i-th index represents the change in the velocity of the i-th body in currentStateOfBodies
        std::vector<Vector2D> deltaPosVectorVector; //< the i-th index represents the change in the position of the i-th body in currentStateOfBodies

        //now calculate the forces
        //meaning, take the currenState of bodies as input and return a vector that consists of vectors representing the forces acting on the corresponding body
        //this can be done either with the naive approach or the barnes-hut algorithm
        switch (algorithmToUse){
            case 0:
                forceVectorVector = naiveAlgorithm.calculateForce(currentStateOfBodies);
                break;
            case 1:
                forceVectorVector = barnesHutAlgorithm.calculateForce(currentStateOfBodies);
                break;
        };
        //now integrate over the force divided by the mass to get the delta-v the body gained
        for (int vectorIndex = 0; vectorIndex < forceVectorVector.size(); ++vectorIndex){
            int mass = currentStateOfBodies[vectorIndex].getWeight();
            deltaVelVectorVector.push_back(integrator.integrate(forceVectorVector[i]/mass, dt));
        }
        //now integrate over the velocity to get the delta-position the body gained
        for (int vectorIndex = 0; vectorIndex < forceVectorVector.size(); ++vectorIndex){
            int mass = currentStateOfBodies[vectorIndex].getWeight();
            deltaVelVectorVector.push_back(integrator.integrate(forceVectorVector[i]/mass, dt));
        }
        //now modify the position, velocity and acceleration of the body in the currentStateOfBodies accordingly
        //check for collision control
        //then, maybe modify the attributes of the bodies in the currentStateOfBodies again
    }
}