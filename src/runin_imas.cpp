#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <UALClasses.h>
#include <vector>
#include "constants.h"
#include "ids_utils.h"
#include "critical_field.h"
#include "growth_rate.h"
#include "codeparams_imas.h"

/*
main function
fix time label

*/
void fire(IdsNs::IDS::core_profiles &core_profiles, IdsNs::IDS::equilibrium &equilibrium, 
       int &critical_field_warning, int &growth_rate_warning, IdsNs::codeparam_t &codeparams) {

	double rho_max = get_rho_cutoff(codeparams);
	double growth_rate_limit = get_growth_rate_limit(codeparams);

	try {
	// critical field: is_field_critical
		critical_field_warning = is_field_critical(
				ids_to_profile(core_profiles, equilibrium,0), rho_max);

	// growth rate: is_growth_rate_over_limit
		growth_rate_warning = is_growth_rate_over_limit(
				ids_to_profile(core_profiles, equilibrium,0), growth_rate_limit, rho_max);

	} catch (const std::exception& ex) {
		std::cerr << "ERROR An error occurred during firing actor Runaway Indicator." << std::endl;
		std::cerr << "ERROR : " << ex.what() << std::endl;
		
		// internal error in critical_field
		critical_field_warning = ITM_INVALID_INT;
		
		// internal error in growth_rate
		growth_rate_warning = ITM_INVALID_INT;
	}
}
