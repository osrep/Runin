#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <UALClasses.h>
#include <vector>
#include "../ext/Runaphys/include/constants.h"
#include "../include/cpo_utils.h"
#include "../ext/Runaphys/include/critical_field.h"
#include "../ext/Runaphys/include/growth_rate.h"
#include "../include/codeparams.h"

/*
main function
fix time label

*/
void fire(ItmNs::Itm::coreprof &coreprof, ItmNs::Itm::coreimpur &coreimpur,
		int &critical_field_warning, int &growth_rate_warning, ItmNs::codeparam_t &codeparams) {

	// set maximum rho value from codeparams
	double rho_max = get_rho_cutoff(codeparams);

	// set the growth rate limit from codeparams
	double growth_rate_limit = get_growth_rate_limit(codeparams);

	try {
	// critical field: is_field_critical
		critical_field_warning = is_field_critical(
				cpo_to_profile(coreprof, coreimpur), rho_max);

	// growth rate: is_growth_rate_over_limit
		growth_rate_warning = is_growth_rate_over_limit(
				cpo_to_profile(coreprof, coreimpur), growth_rate_limit, rho_max);

	} catch (const std::exception& ex) {
		std::cerr << "ERROR An error occurred during firing actor Runaway Indicator." << std::endl;
		std::cerr << "ERROR : " << ex.what() << std::endl;
		
		// internal error in critical_field
		critical_field_warning = ITM_INVALID_INT;
		
		// internal error in growth_rate
		growth_rate_warning = ITM_INVALID_INT;
	}
}
