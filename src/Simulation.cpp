#include <iostream>
#include <cmath>

#include "Simulation.hpp"

Simulation::Simulation
(
    const int dt,
    std::string algorithm,
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

    integrator = std::make_unique<EulerIntegrator>(dt);

}

void Simulation::runStep() {

    std::vector<Body> newStateOfBodies; // describes how currentStateOfBodies will look after the next time step

    // now this will loop over all bodies, update their states and save them in newStateOfBodies
    for (auto iteratorToBody = currentStateOfBodies.begin(); iteratorToBody != currentStateOfBodies.end(); ++iteratorToBody) {

        auto totalForce = forceCalc->getForceOnSingleParticle(currentStateOfBodies, iteratorToBody);

        if (std::isnan(totalForce.x))
            throw std::runtime_error("NaNs in Forces. Abort!");
        else if (totalForce.x > 1e50)
            throw std::runtime_error("Exploding Forces. Abort!");
        

        //dereferencing the iterator just for convenience
        Body newBody = *iteratorToBody;

        //calculate & update acceleration, acceleration in m/(s^2)
        Vector2D deltaAcc = totalForce / (newBody.getWeight() * sunMassToKg);
        Vector2D currentAcc = newBody.getAcc();
        newBody.setAcc(currentAcc + deltaAcc);

        //integrating over the acceleration to get the velocity (in m/s), then updating it
        long double vx = integrator->integrationStep(newBody.getVel().x, newBody.getAcc().x);
        long double vy = integrator->integrationStep(newBody.getVel().y, newBody.getAcc().y);
        Vector2D newVel(vx, vy);
        newBody.setVel(newVel);

        //integrating over the velocity to get the position, then converting from m to Astronomical Units (AU), then updating
        long double x = integrator->integrationStep(newBody.getPos().x * AUtoMeter, newBody.getVel().x) * meterToAU;
        long double y = integrator->integrationStep(newBody.getPos().y * AUtoMeter, newBody.getVel().y) * meterToAU;
        Vector2D newPos(x, y);
        newBody.setPos(newPos);

        //now all the parameters in newBody are up-to-date
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