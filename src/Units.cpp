#include <cmath>

long double G = 6.674e-11; 
long double AUtoMeter = 1.495'978'707e11; //did you know you can use ' as a thousand delimiter like this?
long double meterToAU = 1/AUtoMeter;
long double sunMassToKg = 1.9891e30;
long double conversionFactor = (G*powl(sunMassToKg, 2))/ powl(AUtoMeter, 2);

