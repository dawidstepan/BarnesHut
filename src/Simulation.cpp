#include <iostream>
#include <cmath>

#include "Simulation.hpp"
#include "Integrator.hpp"
#include "EulerIntegrator.hpp"
#include "VerletIntegrator.hpp"
#include "Units.hpp"
#include "gui.hpp"
#include "RenderTargets.hpp"
#include <memory>

Simulation::Simulation
(
    const int dt,
    std::string algorithm,
    std::string usedIntegrator,
    float theta
)
{
    if (algorithm == "Naive") 
    {
        forceCalc = std::make_unique<NaiveForceCalculator>();
    }
    else if (algorithm == "BarnesHut")
    {
        forceCalc = std::make_unique<BarnesHutForceCalculator>(theta);
    }
    else
    {
        throw std::runtime_error("Unknown algorithm! Supported are 'Naive' and 'BarnesHut'");
    }
    
    if (usedIntegrator == "verlet")
    {
        useIntegrator = std::make_unique<VerletIntegrator>();
    }
    else if (usedIntegrator == "euler")
    {
        useIntegrator = std::make_unique<EulerIntegrator>(dt);
    }
    else
    {
        throw std::runtime_error("Unknown Integrator! Supported are 'verlet' and 'euler'");
    }
}

void Simulation::runStep() {
    std::vector<Body> newStateOfBodies;              // describes how currentStateOfBodies will look after the next time step
    std::vector<DataPoint> currentStateOfDataPoints; // this is how we are going to save the data on our disc

    // now this will loop over all bodies, update their states and save them in newStateOfBodies
    for (auto iteratorToBody = currentStateOfBodies.begin(); iteratorToBody != currentStateOfBodies.end(); ++iteratorToBody) {

        auto totalForce = forceCalc->getForceOnSingleParticle(currentStateOfBodies, iteratorToBody);

        if (std::isnan(totalForce.x))
            throw std::runtime_error("NaNs in Forces. Abort!");
        else if (totalForce.x > 1e50)
            throw std::runtime_error("Exploding Forces. Abort!");
        

        //dereferencing the iterator just for convenience
        Body newBody = *iteratorToBody;     
        
        // integrating over the velocity to get the position, then converting from m to Astronomical Units (AU), then updating
        Vector2D newPos = useIntegrator->integratePos(newBody);
        newBody.setPos(newPos);

        // calculate & update acceleration, acceleration in m/(s^2)
        Vector2D currentAcc = newBody.getAcc();
        Vector2D newAcc = totalForce / (newBody.getWeight() * sunMassToKg);
        newBody.setAcc(newAcc);

        // integrating over the acceleration to get the velocity (in m/s), then updating it
        Vector2D newVel = useIntegrator->integrateVel(newBody, currentAcc);
        newBody.setVel(newVel);

        // now all the parameters in newBody are up-to-date
        newStateOfBodies.push_back(newBody);
    }

    // overwrite the current state with the new state, and clear the new state
    currentStateOfBodies.assign(newStateOfBodies.begin(), newStateOfBodies.end());
}


void Simulation::saveStep() {
    std::vector<DataPoint> currentStateOfDataPoints;    // this is how we are going to save the data on our disc
    for (auto iteratorToBody = currentStateOfBodies.begin(); iteratorToBody != currentStateOfBodies.end(); ++iteratorToBody) {
        auto newBody = *iteratorToBody;
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
    }
    stateOfBodiesOverTime.push_back(currentStateOfDataPoints);
}


void Simulation::initializeFromVector(std::vector<Body> StateOfBodies) {
    currentStateOfBodies = StateOfBodies;
}

std::vector<std::vector<DataPoint>> Simulation::getStateOfDataPointsOverTime() {
    return stateOfBodiesOverTime;
}

std::vector<Body> Simulation::getCurrentStateOfBodies() {
    return currentStateOfBodies;
}