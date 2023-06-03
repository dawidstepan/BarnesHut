#ifndef GROUPMPROJECT_EULERINTEGRATOR_HPP
#define GROUPMPROJECT_EULERINTEGRATOR_HPP

#include <Integrator.hpp>
#include <Units.hpp>

/***************************************************************************
 * the euler method is the most basic way to evaluate integrals numerically.
 ***************************************************************************/
class EulerIntegrator : public Integrator {
public:
    virtual Vector2D integrateVel(Body body, long double dt,Vector2D &Da ) override {
        Vector2D currentAcc = body.getAcc();
        Vector2D currentVel = body.getVel();
        Vector2D newVel = currentVel + currentAcc * dt;
        return newVel;
    };

    virtual Vector2D integratePos(Body body, long double dt) override {
        Vector2D currentVel = body.getVel();
        Vector2D currentPos = body.getPos();
        Vector2D newPos = currentPos * AUtoMeter + currentVel * dt;
        return newPos * meterToAU;
    };
};
#endif //GROUPMPROJECT_EULERINTEGRATOR_HPP
