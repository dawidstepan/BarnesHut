#ifndef GROUPMPROJECT_UNITS_HPP
#define GROUPMPROJECT_UNITS_HPP

#include <cmath>

/**
 * Definition of some Units and natural Constants
 */

long double G = 6.674e-11; //Gravitational constant
long double AUtoMeter = 1.495978707e11;
long double meterToAU = 1/AUtoMeter;
long double sunMassToKg = 1.9891e30;
long double conversionFactor = (G*powl(sunMassToKg, 2))/ powl(AUtoMeter, 2);

#endif //GROUPMPROJECT_UNITS_HPP
