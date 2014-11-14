#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <UALClasses.h>

#include "critical_field.h"
#include "growth_rate.h"

double growth_rate_limit = 1e12;

profile cpo_to_profile(ItmNs::Itm::coreprof &coreprof, ItmNs::Itm::coreimpur &coreimpur,
		ItmNs::Itm::equilibrium &equilibrium) {

	profile pro;

	int cells = coreprof.ne.value.rows();
	if (coreprof.te.value.rows() != cells)
		throw std::invalid_argument("Number of values is different in coreprof ne and te.");
	if (coreprof.profiles1d.e_b.value.rows() != cells)
		throw std::invalid_argument(
				"Number of values is different in coreprof.ne and profiles1d.e_b.");
	if (equilibrium.profiles_1d.b_av.rows() != cells)
		throw std::invalid_argument(
				"Number of values is different in coreprof.ne and equilibrium.profiles_1d.b_av.");

	for (int rho = 0; rho < cells; rho++) {
		cell celll;
		celll.electron_density = coreprof.ne.value(rho);
		celll.electron_temperature = coreprof.te.value(rho);
		celll.electric_field = coreprof.profiles1d.e_b.value(rho)
				/ equilibrium.profiles_1d.b_av(rho);
		celll.effective_charge = 0.0;

		for (int ion = 0; ion < coreprof.compositions.ions.rows(); ion++) {
			celll.effective_charge += coreprof.ni.value(rho, ion)
					* coreprof.compositions.ions(ion).zion * coreprof.compositions.ions(ion).zion;
		}

		for (int impurity = 0; impurity < coreimpur.impurity.rows(); impurity++) {
			for (int ionization_degree = 0;
					ionization_degree < coreimpur.impurity(impurity).z.extent(1);
					ionization_degree++) {
				celll.effective_charge += coreimpur.impurity(impurity).nz(rho, ionization_degree)
						* coreimpur.impurity(impurity).z(rho, ionization_degree)
						* coreimpur.impurity(impurity).z(rho, ionization_degree);
			}
		}

// Assume sum of n_i * Z_i equals electron density because of quasi-neutrality
		celll.effective_charge /= celll.electron_density;

		pro.push_back(celll);
	}

	return pro;
}

bool equal(double a, double b, double tolerance) {
	return abs(a - b) * 2.0 > (a + b) * tolerance;
}

void fire(ItmNs::Itm::coreprof &coreprof, ItmNs::Itm::coreimpur &coreimpur,
		ItmNs::Itm::equilibrium &equilibrium, int &critical_field_warning,
		int &growth_rate_warning) {

	critical_field_warning = is_field_critical(cpo_to_profile(coreprof, coreimpur, equilibrium));

	growth_rate_warning = is_growth_rate_over_limit(
			cpo_to_profile(coreprof, coreimpur, equilibrium), growth_rate_limit);
}

void fire(ItmNs::Itm::coreprofArray &coreprof, ItmNs::Itm::coreimpurArray &coreimpur,
		ItmNs::Itm::equilibriumArray &equilibrium, int &critical_field_warning,
		int &growth_rate_warning) {

	critical_field_warning = 0;
	growth_rate_warning = 0;

	int slices = coreprof.array.rows();
	if (coreimpur.array.rows() != slices)
		throw std::invalid_argument("Number of cpo slices is different in coreprof and coreimpur.");
	if (equilibrium.array.rows() != slices)
		throw std::invalid_argument(
				"Number of cpo slices is different in coreprof and equilibrium.");

	for (int slice = 0; slice < slices; slice++) {

		if (!equal(coreprof[slice].time, coreimpur[slice].time, 0.01)
				|| !equal(coreprof[slice].time, equilibrium[slice].time, 0.01))
			throw std::invalid_argument("Time value differs in cpo slices of the same index.");

		if (critical_field_warning == 0)
			critical_field_warning = is_field_critical(
					cpo_to_profile(coreprof[slice], coreimpur[slice], equilibrium[slice]));

		if (growth_rate_warning == 0)
			growth_rate_warning = is_growth_rate_over_limit(
					cpo_to_profile(coreprof[slice], coreimpur[slice], equilibrium[slice]),
					growth_rate_limit);
	}
}
