#pragma once

#include <vector>
#include "Vector2D.hpp"
#include <memory>
#include "Body.hpp"

/****************************************************************************
 * This Interface allows to switch between time integration methods.
 ***************************************************************************/

 class Integrator {
    public:

        virtual Vector2D integrateVel(Body &newBody,Vector2D &Da )=0;
        virtual Vector2D integratePos(Body &newBody)=0;
        virtual ~Integrator() {}  

 };
