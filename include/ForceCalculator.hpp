#pragma once

#include "Node.hpp"
#include "BarnesHut.hpp"
#include <vector>
#include <Body.hpp>
#include <Units.hpp>
#include <memory>

struct ForceCalculator {

    virtual void initializeFromParticles(std::vector<Body> &currentStateOfBodies) = 0;

    virtual Vector2D getForceOnSingleParticle(std::vector<Body> &currentStateOfBodies, std::vector<Body>::iterator iteratorToBody) = 0;

    virtual ~ForceCalculator() {};
};


struct NaiveForceCalculator : ForceCalculator {

    void initializeFromParticles(std::vector<Body> &currentStateOfBodies) override;

    Vector2D getForceOnSingleParticle(std::vector<Body> &currentStateOfBodies, std::vector<Body>::iterator iteratorToBody) override;

};


struct BarnesHutForceCalculator : ForceCalculator {
    BarnesHutForceCalculator(float theta);

    void initializeFromParticles(std::vector<Body>& currentStateOfBodies) override;

    Vector2D getForceOnSingleParticle(std::vector<Body>& currentStateOfBodies, std::vector<Body>::iterator iteratorToBody) override;

private:
    std::unique_ptr<Node> node;
    std::unique_ptr<BarnesHut> barneshut; // computed in initializeFromParticles
    float theta;
};