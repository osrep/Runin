#include <cmath>
#include "growth_rate.h"

double me_c2 = ITM_ME * pow(ITM_C, 2);
double me2_c3 = me_c2 * ITM_ME * ITM_C;
double me2_c3__e = me2_c3 / ITM_QE;
double pi_4_e02_me2_c3__e4 = ITM_PI * 4.0 * pow(ITM_EPS0, 2) * me2_c3 / pow(ITM_QE, 4);

int is_growth_rate_over_limit(profile pro, double limit) {

	for (std::vector<cell>::iterator it = pro.begin(); it != pro.end(); ++it) {
		if (calculate_growth_rate(it->electron_density, it->electron_temperature,
				it->effective_charge, it->electric_field) > limit)
			return 1;
	}

	return 0;
}

double calculate_growth_rate(double electron_density, double electron_temperature,
		double effective_charge, double electric_field) {

	double coulomb_log = 14.9 - 0.5 * log(electron_density * 1e-20)
			+ log(electron_temperature * 1e-3);

	double tao = pi_4_e02_me2_c3__e4 / (electron_density * coulomb_log);

	double Ed = me2_c3__e / (tao * electron_temperature);

	return electron_density / tao * pow(me_c2 / (2.0 * electron_temperature), 1.5)
			* pow(Ed / electric_field, 3.0 * (1.0 + effective_charge) / 16.0)
			* exp(-Ed / (4.0 * electric_field) - sqrt((1 + effective_charge) * Ed / electric_field));
}
