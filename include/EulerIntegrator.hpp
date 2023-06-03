#ifndef GROUPMPROJECT_EULERINTEGRATOR_HPP
#define GROUPMPROJECT_EULERINTEGRATOR_HPP

#include <Integrator.hpp>
#include <Units.hpp>

/***************************************************************************
 * the euler method is the most basic way to evaluate integrals numerically.
 ***************************************************************************/
class EulerIntegrator : public Integrator {
public:

    EulerIntegrator(): Integrator(), timestep(0) {};

    virtual Vector2D integrateVel(Body body, Vector2D &Da ) override {
        Vector2D currentAcc = body.getAcc();
        Vector2D currentVel = body.getVel();
        Vector2D newVel = currentVel + currentAcc * timestep;
        return newVel;
    };

    virtual Vector2D integratePos(Body body) override {
        Vector2D currentVel = body.getVel();
        Vector2D currentPos = body.getPos();
        Vector2D newPos = currentPos * AUtoMeter + currentVel * timestep;
        return newPos * meterToAU;
    };

    private:

    int timestep;
};

#endif //GROUPMPROJECT_EULERINTEGRATOR_HPP