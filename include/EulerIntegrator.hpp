#ifndef GROUPMPROJECT_EULERINTEGRATOR_HPP
#define GROUPMPROJECT_EULERINTEGRATOR_HPP

/**
 * the euler method is the most basic way to evaluate integrals numerically
 * (header-only)
 */
class EulerIntegrator {
public:
    long double integrationStep(long double initialValue,long double dt,long double f_t){
        long double step = f_t * dt;
        long double newValue = initialValue + step;
        return newValue;
    };
};
#endif //GROUPMPROJECT_EULERINTEGRATOR_HPP
