#ifndef GROUPMPROJECT_GENERALPARAMETERS_HPP
#define GROUPMPROJECT_GENERALPARAMETERS_HPP


/**
 * \brief just a convenient way of storing all the general parameters grouped together
 * (header-only)
 */
struct GeneralParameters {
    float theta;    /// describes the quality of our Barnes-Hut approximation
    int dt;         /// timestep in seconds
    int totalNumberOfSteps;
    int saveOnEveryXthStep;
    int algorithmToUse; /// 0=naive approach, 1=Barnes Hut
    int IntegratorToUse; /// 0=euler, 1=verlet

};

#endif //GROUPMPROJECT_GENERALPARAMETERS_HPP
