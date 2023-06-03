#pragma once

#include <Integrator.hpp>
#include <Units.hpp>
#include <iostream>

/****************************************************************************
 * the verlet integration method is an advanced way to evaluate integrals numerically.
 ***************************************************************************/

 class VerletIntegrator : public Integrator {
    public:

    VerletIntegrator(long double dt): timestep(dt) {};
        

        virtual Vector2D integrateVel(Body &body, Vector2D &currentAcc ) override {
            Vector2D currentVel = body.getVel();
            Vector2D newAcc = body.getAcc();
            Vector2D newVel = currentVel + (newAcc + currentAcc ) * timestep * 0.5;
            return newVel;
            };

        virtual Vector2D integratePos(Body &body) override {
            Vector2D currentVel = body.getVel();
            Vector2D currentPos = body.getPos();
            Vector2D currentAcc = body.getAcc();
            Vector2D newPos = currentPos * AUtoMeter + currentVel *  timestep + currentAcc * 0.5 * timestep * timestep;
            return newPos * meterToAU;
            };

    private:

    long double timestep;


 };