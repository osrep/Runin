#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <vector>

#define ITM_PI		3.141592653589793238462643383280
#define ITM_C		2.99792458e8  // speed of light [m/s]
#define ITM_EV		1.602176565e-19  // electron volt (eV)
#define ITM_QE		ITM_EV  // elementary charge [coulomb]
#define ITM_ME		9.10938291e-31  // electron mass [kg]
#define ITM_MU0		4.0e-7 * ITM_PI  // vacuum permeability
#define ITM_EPS0	1.0 / (ITM_MU0 * ITM_C * ITM_C)

#define ITM_ILLEGAL_INT	-999999999

struct cell {
	double electron_density;
	double electron_temperature;
	double effective_charge;
	double electric_field;
};

typedef std::vector<cell> profile;

#endif /* CONSTANTS_H_ */
