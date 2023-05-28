#ifndef GROUPMPROJECT_VERLETINTEGRATOR_HPP
#define GROUPMPROJECT_VERLETINTEGRATOR_HPP

#include <Integrator.hpp>
#include <Units.hpp>

/**
 * the verlet integration method is an advanced way to evaluate integrals numerically
 * (header-only)
 */

 class VerletIntegrator : public Integrator {
    public:
        virtual Vector2D integrateVel(Body body, long double dt, Vector2D &delacc ) override {
            Vector2D currentVel = body.getVel();
            Vector2D currentAcc = body.getAcc();
            Vector2D newVel = currentVel + (currentAcc - delacc * 0.5) * dt; // THIS IS NOT CORRECT !!!!!!!!!!!!!!
            return newVel;
            };

        virtual Vector2D integratePos(Body body, long double dt) override {
            Vector2D currentVel = body.getVel();
            Vector2D currentPos = body.getPos();
            Vector2D currentAcc = body.getAcc();
            Vector2D newPos = currentPos * AUtoMeter + currentVel *  dt + (currentVel) * dt + currentAcc * 0.5 * dt * dt;
            return newPos * meterToAU;
            };
 };

 #endif //GROUPMPROJECT_VERLETINTEGRATOR_HPP