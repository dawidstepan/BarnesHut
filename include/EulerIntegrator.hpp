#ifndef GROUPMPROJECT_EULERINTEGRATOR_HPP
#define GROUPMPROJECT_EULERINTEGRATOR_HPP

/**
 * the euler method is the most basic way to evaluate integrals numerically
 * (header-only)
 */
class EulerIntegrator {
public:
    long double integrationStep(long double initialValue,long double dt,long double f_t){

        //std::cout << "---\nintegrator called with initial value: " << initialValue << std::endl;
        long double step = f_t * dt;
        //std::cout << "step: " << step <<std::endl;
        long double newValue = initialValue + step;
        //std::cout << "initial value + step: " << newValue <<std::endl;
        return newValue;
    };
};
#endif //GROUPMPROJECT_EULERINTEGRATOR_HPP
