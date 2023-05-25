#include <iostream>
#include "Simulation.hpp"
#include "EulerIntegrator.hpp"
#include "Units.hpp"
#include "gui.hpp"
#include "RenderTargets.hpp"

void Simulation::runSimulation() {

    EulerIntegrator eulerIntegrator; // Euler Method is the most basic way of numerical integration
    std::vector<Body> newStateOfBodies; // describes how currentStateOfBodies will look after the next time step
    std::vector<DataPoint> currentStateOfDataPoints;    // this is how we are going to save the data on our disc

    //loop over all time steps
    for (int i=0; i < generalParameters.totalNumberOfSteps; i++){
        // now this will loop over all bodies, update their states and save them in newStateOfBodies
        for (auto iteratorToBody = currentStateOfBodies.begin(); iteratorToBody != currentStateOfBodies.end(); ++iteratorToBody) {
            // calculating the total force with the algorithm the 'getForce' pointer is set to

            Vector2D totalForce;
            switch (generalParameters.algorithmToUse){
                case 0: //this means we will use the simplest, brute-force-ish approach to calculate the force
                    totalForce = getForceByNaiveAlgorithm(currentStateOfBodies, iteratorToBody);
                    break;
                case 1: //this means we will use the more sophisticated Barnes-Hut algorithm to approximate the force
                    totalForce = getForceByBarnesHutAlgorithm(currentStateOfBodies, iteratorToBody);
                    break;
            }

            //dereferencing the iterator just for convenience
            Body newBody = *iteratorToBody;

            //calculate & update acceleration, acceleration in m/(s^2)
            Vector2D deltaAcc = totalForce/(newBody.getWeight()*sunMassToKg);
            Vector2D currentAcc = newBody.getAcc();
            newBody.setAcc(currentAcc + deltaAcc);

            //integrating over the acceleration to get the velocity (in m/s), then updating it
            long double vx = eulerIntegrator.integrationStep(newBody.getVel().x, generalParameters.dt, newBody.getAcc().x);
            long double vy = eulerIntegrator.integrationStep(newBody.getVel().y, generalParameters.dt, newBody.getAcc().y);
            Vector2D newVel(vx, vy);
            newBody.setVel(newVel);

            //integrating over the velocity to get the position, then converting from m to Astronomical Units (AU), then updating
            long double x = eulerIntegrator.integrationStep(newBody.getPos().x * AUtoMeter, generalParameters.dt, newBody.getVel().x) * meterToAU;
            long double y = eulerIntegrator.integrationStep(newBody.getPos().y * AUtoMeter, generalParameters.dt, newBody.getVel().y) * meterToAU;
            Vector2D newPos(x, y);
            newBody.setPos(newPos);

            //now all the parameters in newBody are up-to-date
            newStateOfBodies.push_back(newBody);

            //we're going to save dataPoints on disc instead of body objects - they need less volume
            DataPoint dataPoint{};
            dataPoint.size = newBody.getSize();
            dataPoint.weight = newBody.getWeight();
            dataPoint.x = newBody.getPos().x;
            dataPoint.y = newBody.getPos().y;
            dataPoint.vx = newBody.getVel().x;
            dataPoint.vy = newBody.getVel().y;
            dataPoint.ax = newBody.getAcc().x;
            dataPoint.ay = newBody.getAcc().y;
            currentStateOfDataPoints.push_back(dataPoint);

            // std::cout << "Body at (" << newPos.x << ", " << newPos.y << ") [AU]: \n"
            //             << "\tcurrent force: " << totalForce.y << " N\n"
            //             << "\tcurrent velocity: " << newVel.y << " m/s\n"<< std::endl;
        }
        // we might not want to save to memory on this particular iteration, but if we do, update the StateOfBodiesOverTime vector
        if (i % generalParameters.saveOnEveryXthStep == 0) {
            stateOfBodiesOverTime.push_back(currentStateOfDataPoints);
        }


        // overwrite the current state with the new state, and clear the new state
        currentStateOfBodies.assign(newStateOfBodies.begin(), newStateOfBodies.end());
        newStateOfBodies.clear();
        currentStateOfDataPoints.clear();
    }
}



// * * * * * * * * * * * * * *
// *  yet to be implemented! *
// * * * * * * * * * * * * * *
Vector2D Simulation::getForceByBarnesHutAlgorithm(std::vector<Body>, std::vector<Body>::iterator iteratorToBody){
    std::cout << "this is the barnes hut algorithm lul" << std::endl;
}

/// the most basic approach to calculating the force between the objects
Vector2D Simulation::getForceByNaiveAlgorithm(std::vector<Body>, std::vector<Body>::iterator iteratorToBody) {
    Vector2D totalForce(0, 0);
    for (auto iteratorToOtherBody = currentStateOfBodies.begin(); iteratorToOtherBody != currentStateOfBodies.end(); ++iteratorToOtherBody){
        //check if we aren't comparing the same bodies with each other
        if (iteratorToBody != iteratorToOtherBody) {
            //getting relevant data
            Vector2D pos1 = iteratorToBody->getPos();
            Vector2D pos2 = iteratorToOtherBody->getPos();
            long double m1 = iteratorToBody->getWeight();
            long double m2 = iteratorToOtherBody->getWeight();
            /*
             * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
             *  maybe here would be a good place to call a collision-detection function? *
             * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */
            //we are just rn computing the distance, after all
            Vector2D distanceVector = pos2-pos1;
            long double distanceNorm = distanceVector.getNorm();
            //calculating the force (in newton)
            Vector2D force = distanceVector*((m1*m2))/((distanceNorm * distanceNorm * distanceNorm))*conversionFactor;
            totalForce =  totalForce + force;
            return totalForce;
        }
    }

}