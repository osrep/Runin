#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <UALClasses.h>
#include <vector>
#include "constants.h"
#include "cpo_utils.h"
#include "critical_field.h"
#include "growth_rate.h"

/*
main function
fix time label

*/
void fire(ItmNs::Itm::coreprof &coreprof, ItmNs::Itm::coreimpur &coreimpur, double &growth_rate_limit,
		int &critical_field_warning, int &growth_rate_warning) {

	try {
	// critical field: is_field_critical
		critical_field_warning = is_field_critical(
				cpo_to_profile(coreprof, coreimpur));

	// growth rate: is_growth_rate_over_limit
		growth_rate_warning = is_growth_rate_over_limit(
				cpo_to_profile(coreprof, coreimpur), growth_rate_limit);

	} catch (const std::exception& ex) {
		std::cerr << "ERROR An error occurred during firing actor Runaway Indicator." << std::endl;
		std::cerr << "ERROR : " << ex.what() << std::endl;
		
		// internal error in critical_field
		critical_field_warning = ITM_INVALID_INT;
		
		// internal error in growth_rate
		growth_rate_warning = ITM_INVALID_INT;
	}
}
