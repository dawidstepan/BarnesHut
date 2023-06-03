#ifndef GROUPMPROJECT_INTEGRATOR_HPP
#define GROUPMPROJECT_INTEGRATOR_HPP

#include <vector>
#include "Vector2D.hpp"

/****************************************************************************
 * This Interface allows to switch between time integration methods.
 ***************************************************************************/

 class Integrator {
    public:

        virtual Vector2D integrateVel(Body body,Vector2D &Da )=0;
        virtual Vector2D integratePos(Body body)=0;
        Integrator(): timestep(0) {};
        virtual ~Integrator() {}  

    private:
        int timestep;     
 };

    

 #endif //GROUPMPROJECT_INTEGRATOR_HPP