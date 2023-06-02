#pragma once

#include <vector>
#include <Body.hpp>
#include <Units.hpp>

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

    void initializeFromParticles(std::vector<Body> &currentStateOfBodies) override;

    Vector2D getForceOnSingleParticle(std::vector<Body> &currentStateOfBodies, std::vector<Body>::iterator iteratorToBody) override;

    private:
        int BarnesHutTree; // computed in initalizeFromParticles
};