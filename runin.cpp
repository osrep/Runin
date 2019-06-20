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
void fire(ItmNs::Itm::coreprof &coreprof, ItmNs::Itm::coreimpur &coreimpur,
		ItmNs::Itm::equilibrium &equilibrium, double &growth_rate_limit,
		int &critical_field_warning, int &growth_rate_warning) {

	try {
	// critical field: is_field_critical
		critical_field_warning = is_field_critical(
				cpo_to_profile(coreprof, coreimpur, equilibrium));

	// growth rate: is_growth_rate_over_limit
		growth_rate_warning = is_growth_rate_over_limit(
				cpo_to_profile(coreprof, coreimpur, equilibrium), growth_rate_limit);

	} catch (const std::exception& ex) {
		std::cerr << "ERROR An error occurred during firing actor Runaway Indicator." << std::endl;
		std::cerr << "ERROR : " << ex.what() << std::endl;
		
		// internal error in critical_field
		critical_field_warning = ITM_INVALID_INT;
		
		// internal error in growth_rate
		growth_rate_warning = ITM_INVALID_INT;
	}
}

/*
main function
arrays by time

*/
void fire(ItmNs::Itm::coreprofArray &coreprof, ItmNs::Itm::coreimpurArray &coreimpur,
		ItmNs::Itm::equilibriumArray &equilibrium, double &growth_rate_limit,
		int &critical_field_warning, int &growth_rate_warning, double &critical_field_time,
		double &growth_rate_time) {

	critical_field_warning = 0;
	growth_rate_warning = 0;

	try {
		int slices = coreprof.array.rows();
		if (coreimpur.array.rows() != slices)
			throw std::invalid_argument(
					"Number of cpo slices is different in coreprof and coreimpur.");
		if (equilibrium.array.rows() != slices)
			throw std::invalid_argument(
					"Number of cpo slices is different in coreprof and equilibrium.");

		int slice = 0;
		for (slice = 0; slice < slices; slice++) {

			if (!equal(coreprof[slice].time, coreimpur[slice].time, 0.01)
					|| !equal(coreprof[slice].time, equilibrium[slice].time, 0.01))
				throw std::invalid_argument("Time value differs in cpo slices of the same index.");

			// critical field: is_field_critical
			if (critical_field_warning == 0) {
				critical_field_warning = is_field_critical(
						cpo_to_profile(coreprof[slice], coreimpur[slice], equilibrium[slice]));

				if (critical_field_warning != 0)
					critical_field_time = coreprof[slice].time;
			}

			// growth rate: is_growth_rate_over_limit
			if (growth_rate_warning == 0) {
				growth_rate_warning = is_growth_rate_over_limit(
						cpo_to_profile(coreprof[slice], coreimpur[slice], equilibrium[slice]),
						growth_rate_limit);

				if (growth_rate_warning != 0)
					growth_rate_time = coreprof[slice].time;
			}
		}

	} catch (const std::exception& ex) {
		std::cerr << "ERROR An error occurred during firing actor Runaway Indicator." << std::endl;
		std::cerr << "ERROR : " << ex.what() << std::endl;

		// internal error in critical_field
		critical_field_warning = ITM_INVALID_INT;
		
		// internal error in growth_rate
		growth_rate_warning = ITM_INVALID_INT;
	}
}
