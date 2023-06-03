#pragma once

#include <Integrator.hpp>
#include <Units.hpp>

/***************************************************************************
 * the euler method is the most basic way to evaluate integrals numerically.
 ***************************************************************************/
class EulerIntegrator : public Integrator {
public:

    EulerIntegrator(long double dt): timestep(dt) {};

    virtual Vector2D integrateVel(Body &body, Vector2D &currentAcc ) override {
        Vector2D currentVel = body.getVel();
        Vector2D newVel = currentVel + currentAcc * timestep;
        return newVel;
    };

    virtual Vector2D integratePos(Body &body) override {
        Vector2D currentVel = body.getVel();
        Vector2D currentPos = body.getPos();
        Vector2D newPos = currentPos * AUtoMeter + currentVel * timestep;
        return newPos * meterToAU;
    };

    private:

    long double timestep;

};