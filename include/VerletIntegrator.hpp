#ifndef GROUPMPROJECT_VERLETINTEGRATOR_HPP
#define GROUPMPROJECT_VERLETINTEGRATOR_HPP

#include <Integrator.hpp>
#include <Units.hpp>

/****************************************************************************
 * the verlet integration method is an advanced way to evaluate integrals numerically.
 ***************************************************************************/

 class VerletIntegrator : public Integrator {
    public:

    VerletIntegrator(): Integrator(), timestep(0) {};
        

        virtual Vector2D integrateVel(Body body, Vector2D &delacc ) override {
            Vector2D currentVel = body.getVel();
            Vector2D currentAcc = body.getAcc();
            Vector2D newVel = currentVel + (currentAcc - delacc * 0.5) * timestep;
            return newVel;
            };

        virtual Vector2D integratePos(Body body) override {
            Vector2D currentVel = body.getVel();
            Vector2D currentPos = body.getPos();
            Vector2D currentAcc = body.getAcc();
            Vector2D newPos = currentPos * AUtoMeter + currentVel *  timestep + (currentVel) * timestep + currentAcc * 0.5 * timestep * timestep;
            return newPos * meterToAU;
            };

    private:

    int timestep;
 };

#endif //GROUPMPROJECT_VERLETINTEGRATOR_HPP