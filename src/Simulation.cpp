#include <iostream>
#include "Simulation.hpp"
#include "EulerIntegrator.hpp"
#include "VerletIntegrator.hpp"
#include "Units.hpp"
#include <memory>

void Simulation::runSimulation()
{
    // this line creates a special pointer to a member function of the Simulation class
    Vector2D (Simulation::*getForce)(std::vector<Body> *, std::vector<Body>::iterator iteratorToBody);
    // depending on the user input, that is stored in generalParameters, this member pointer will point to a different function
    switch (generalParameters->algorithmToUse)
    {
    case 0: // this means we will use the simplest, brute-force-ish approach to calculate the force
        getForce = &Simulation::getForceByNaiveAlgorithm;
        break;
    case 1: // this means we will use the more sophisticated Barnes-Hut algorithm to approximate the force
        getForce = &Simulation::getForceByBarnesHutAlgorithm;
        break;
    }

    // this line creates pointer with the Interface class as type
    std::unique_ptr<Integrator> useIntegrator;

    // depending on the user input, that is stored in generalParameters, this pointer will point and create an instance of a different class
    switch (generalParameters->IntegratorToUse)
    {
    case 0: // this means we will use the euler method to integrate
        useIntegrator = std::make_unique<EulerIntegrator>();
        break;
    case 1: // this means we will use the velocity verlet method to integrate
        useIntegrator = std::make_unique<VerletIntegrator>();
        break;
    }

    std::vector<Body> newStateOfBodies;              // describes how currentStateOfBodies will look after the next time step
    std::vector<DataPoint> currentStateOfDataPoints; // this is how we are going to save the data on our disc

    // loop over all time steps
    for (int i = 0; i < generalParameters->totalNumberOfSteps; i++)
    {
        // now this will loop over all bodies, update their states and save them in newStateOfBodies
        for (auto iteratorToBody = currentStateOfBodies->begin(); iteratorToBody != currentStateOfBodies->end(); ++iteratorToBody)
        {
            // calculating the total force with the algorithm the 'getForce' pointer is set to
            Vector2D totalForce = ((*this).*(getForce))(currentStateOfBodies, iteratorToBody);

            // dereferencing the iterator just for convenience
            Body newBody = *iteratorToBody;

            // integrating over the velocity to get the position, then converting from m to Astronomical Units (AU), then updating
            Vector2D newPos = useIntegrator->integratePos(newBody, generalParameters->dt);
            newBody.setPos(newPos);

            // calculate & update acceleration, acceleration in m/(s^2)
            Vector2D deltaAcc = totalForce / (newBody.getWeight() * sunMassToKg);
            Vector2D currentAcc = newBody.getAcc();
            newBody.setAcc(currentAcc + deltaAcc);

            // integrating over the acceleration to get the velocity (in m/s), then updating it
            Vector2D newVel = useIntegrator->integrateVel(newBody, generalParameters->dt, currentAcc);
            newBody.setVel(newVel);

            // now all the parameters in newBody are up-to-date
            newStateOfBodies.push_back(newBody);

            // we're going to save dataPoints on disc instead of body objects - they need less volume
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

            std::cout << "Body at (" << newPos.x << ", " << newPos.y << ") [AU]: \n"
                      << "\tcurrent force: " << totalForce.y << " N\n"
                      << "\tcurrent velocity: " << newVel.y << " m/s\n"
                      << std::endl;
        }
        // we might not want to save to memory on this particular iteration, but if we do, update the StateOfBodiesOverTime vector
        if (i % generalParameters->saveOnEveryXthStep == 0)
        {
            updateStateOfBodiesOverTime(currentStateOfDataPoints);
        }
        // overwrite the current state with the new state, and clear the new state
        currentStateOfBodies->assign(newStateOfBodies.begin(), newStateOfBodies.end());
        newStateOfBodies.clear();
    }
}

// * * * * * * * * * * * * * *
// *  yet to be implemented! *
// * * * * * * * * * * * * * *
Vector2D Simulation::getForceByBarnesHutAlgorithm(std::vector<Body> *, std::vector<Body>::iterator iteratorToBody)
{
    std::cout << "this is the barnes hut algorithm lul" << std::endl;
}

/// the most basic approach to calculating the force between the objects
Vector2D Simulation::getForceByNaiveAlgorithm(std::vector<Body> *, std::vector<Body>::iterator iteratorToBody)
{
    Vector2D totalForce(0, 0);
    for (auto iteratorToOtherBody = currentStateOfBodies->begin(); iteratorToOtherBody != currentStateOfBodies->end(); ++iteratorToOtherBody)
    {
        // check if we aren't comparing the same bodies with each other
        if (iteratorToBody != iteratorToOtherBody)
        {
            // getting relevant data
            Vector2D pos1 = iteratorToBody->getPos();
            Vector2D pos2 = iteratorToOtherBody->getPos();
            long double m1 = iteratorToBody->getWeight();
            long double m2 = iteratorToOtherBody->getWeight();
            /*
             * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
             *  maybe here would be a good place to call a collision-detection function? *
             * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
             */
            // we are just rn computing the distance, after all
            Vector2D distanceVector = pos2 - pos1;
            long double distanceNorm = distanceVector.getNorm();
            // calculating the force (in newton)
            Vector2D force = distanceVector * ((m1 * m2)) / ((distanceNorm * distanceNorm * distanceNorm)) * conversionFactor;
            totalForce = totalForce + force;
            return totalForce;
        }
    }
}

void Simulation::updateStateOfBodiesOverTime(std::vector<DataPoint> currentStateOfDataPoints)
{
    stateOfBodiesOverTime->push_back(currentStateOfDataPoints);
};
