#pragma once
/**
 * the euler method is the most basic way to evaluate integrals numerically
 * (header-only)
 */
class EulerIntegrator {
public:

    EulerIntegrator(long double dt) : timestep(dt) {};

    long double integrationStep(long double initialValue, long double f_t){
        long double step = f_t * timestep;
        long double newValue = initialValue + step;
        return newValue;
    };

private:
    long double timestep;
};
