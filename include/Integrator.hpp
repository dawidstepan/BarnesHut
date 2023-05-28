#ifndef GROUPMPROJECT_INTEGRATOR_HPP
#define GROUPMPROJECT_INTEGRATOR_HPP

#include <vector>
#include "Vector2D.hpp"

/**
 * the verlet integration method is an advanced way to evaluate integrals numerically
 * (header-only)
 */

 class Integrator {
    public:
        virtual Vector2D integrateVel(Body body, long double dt,Vector2D &Da )=0;
        virtual Vector2D integratePos(Body body, long double dt)=0;
        virtual ~Integrator() {}
        
 };

 #endif //GROUPMPROJECT_INTEGRATOR_HPP