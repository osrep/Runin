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

/*
main function
fix time label

*/
void fire(IdsNs::IDS::core_profiles &core_profiles, IdsNs::IDS::equilibrium &equilibrium, 
        double &growth_rate_limit,	int &critical_field_warning, int &growth_rate_warning) {

	try {
	// critical field: is_field_critical
		critical_field_warning = is_field_critical(
				ids_to_profile(core_profiles, equilibrium,0));

	// growth rate: is_growth_rate_over_limit
		growth_rate_warning = is_growth_rate_over_limit(
				ids_to_profile(core_profiles, equilibrium,0), growth_rate_limit);

	} catch (const std::exception& ex) {
		std::cerr << "ERROR An error occurred during firing actor Runaway Indicator." << std::endl;
		std::cerr << "ERROR : " << ex.what() << std::endl;
		
		// internal error in critical_field
		critical_field_warning = ITM_INVALID_INT;
		
		// internal error in growth_rate
		growth_rate_warning = ITM_INVALID_INT;
	}
}

/*!
main function

arrays by time*/
/*
void fire(IdsNs::IDS::core_profiles &core_profiles, IdsNs::IDS::equilibrium &equilibrium,
        double &growth_rate_limit,	int &critical_field_warning, int &growth_rate_warning,
        double &critical_field_time, double &growth_rate_time) {

	critical_field_warning = 0;
	growth_rate_warning = 0;

	try {
		int slices = core_profiles.profiles_1d.rows();
		if (equilibrium.time_slice.rows() != slices)
			throw std::invalid_argument(
					"Number of cpo slices is different in core_profiles and equilibrium.");

		int slice = 0;
		for (slice = 0; slice < slices; slice++) {

			if (!equal(core_profiles.time(slice), equilibrium.time(slice), 0.01))
				throw std::invalid_argument("Time value differs in cpo slices of the same index.");

			//! critical field: \sa is_field_critical
			if (critical_field_warning == 0) {
				critical_field_warning = is_field_critical(
						ids_to_profile(core_profiles, equilibrium, slice));

				if (critical_field_warning != 0)
					critical_field_time = core_profiles.time(slice);
			}

			//! growth rate: \sa is_growth_rate_over_limit
			if (growth_rate_warning == 0) {
				growth_rate_warning = is_growth_rate_over_limit(
						ids_to_profile(core_profiles, equilibrium, slice),
						growth_rate_limit);

				if (growth_rate_warning != 0)
					growth_rate_time = core_profiles.time(slice);
			}
		}

	} catch (const std::exception& ex) {
		std::cerr << "ERROR An error occurred during firing actor Runaway Indicator." << std::endl;
		std::cerr << "ERROR : " << ex.what() << std::endl;

		//! internal error in critical_field
		critical_field_warning = ITM_INVALID_INT;
		
		//! internal error in growth_rate
		growth_rate_warning = ITM_INVALID_INT;
	}
}*/
