#include "Body.hpp"
#include "ForceCalculator.hpp"
#include "BarnesHut.hpp"
#include "Node.hpp"
#include "Units.hpp"
#include <cmath>
#include <vector>

void NaiveForceCalculator::initializeFromParticles(std::vector<Body> &currentStateOfBodies) {}

Vector2D NaiveForceCalculator::getForceOnSingleParticle(std::vector<Body> &currentStateOfBodies, std::vector<Body>::iterator iteratorToBody) {
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
            Vector2D distanceVector = pos2 - pos1;
            long double distanceNorm = distanceVector.getNorm();
            //calculating the force (in newton)
            Vector2D force = distanceVector * (m1 * m2) / (distanceNorm * distanceNorm * distanceNorm) * conversionFactor;
            totalForce =  totalForce + force;
        }
    }
    return totalForce;
}


BarnesHutForceCalculator::BarnesHutForceCalculator(float theta) : theta(theta) {}

void BarnesHutForceCalculator::initializeFromParticles(std::vector<Body>& currentStateOfBodies) {
    // Initialize Barnes-Hut and build tree
    barneshut = std::make_unique<BarnesHut>(currentStateOfBodies, theta);
    node = barneshut->buildTree();
}

Vector2D BarnesHutForceCalculator::getForceOnSingleParticle(std::vector<Body>& currentStateOfBodies, std::vector<Body>::iterator iteratorToBody) {
    Vector2D force(0, 0);

    // Calculate forces
    force = barneshut->calculateForceFromNode(node, iteratorToBody) * conversionFactor / G;

    return force;
}


