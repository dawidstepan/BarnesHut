#ifndef GROUPMPROJECT_INTEGRATOR_HPP
#define GROUPMPROJECT_INTEGRATOR_HPP

#include <vector>
#include "Vector2D.hpp"

/****************************************************************************
 * This Interface allows to switch between time integration methods.
 ***************************************************************************/

 class Integrator {
    public:
        virtual Vector2D integrateVel(Body body, long double dt,Vector2D &Da )=0;
        virtual Vector2D integratePos(Body body, long double dt)=0;
        virtual ~Integrator() {}
        
 };

 #endif //GROUPMPROJECT_INTEGRATOR_HPP