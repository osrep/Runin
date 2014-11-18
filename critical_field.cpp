#include <cmath>
#include "critical_field.h"

double e3 = pow(ITM_QE, 3);
double pi_e02_me_4_c2 = ITM_PI * pow(ITM_EPS0, 2) * ITM_ME * 4.0 * pow(ITM_C, 2);

int is_field_critical(profile pro) {

	for (std::vector<cell>::iterator it = pro.begin(); it != pro.end(); ++it) {
		if (calculate_critical_field(it->electron_density, it->electron_temperature)
				< it->electric_field)
			return 1;
	}

	return 0;
}

double calculate_critical_field(double electron_density, double electron_temperature) {

	double coulomb_log = 14.9 - 0.5 * log(electron_density * 1e-20)
			+ log(electron_temperature * 1e-3);

	return electron_density * e3 * coulomb_log / pi_e02_me_4_c2;
}
