#include <algorithm>
#include <stdexcept>
#include <UALClasses.h>

#include "critical_field.h"
#include "growth_rate.h"

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

	for (int r = 0; r < cells; r++) {
		cell celll;
		celll.electron_density = coreprof.ne.value(r);
		celll.electron_temperature = coreprof.te.value(r);
		celll.electric_field = coreprof.profiles1d.e_b.value(r) / equilibrium.profiles_1d.b_av(r);
		celll.effective_charge = 0.0;

		for (int ion = 0; ion < coreprof.compositions.ions.rows(); ion++) {
			celll.effective_charge += coreprof.ni.value(r, ion)
					* coreprof.compositions.ions(ion).zion * coreprof.compositions.ions(ion).zion;
		}

		for (int impur = 0; impur < coreimpur.impurity.rows(); impur++) {
			celll.effective_charge += coreimpur.impurity(impur).nz(r)
					* coreimpur.impurity(impur).z(r) * coreimpur.impurity(impur).z(r);
		}

		// Assume sum of n_i * Z_i equals electron density because of quasi-neutrality
		celll.effective_charge /= celll.electron_density;

		pro.push_back(celll);
	}

	return pro;
}

void fire(ItmNs::Itm::coreprofArray &coreprof, ItmNs::Itm::coreimpurArray &coreimpur,
		ItmNs::Itm::equilibriumArray &equilibrium, double &growth_rate_limit,
		bool &critical_field_warning, bool &growth_rate_warning) {

	critical_field_warning = false;
	growth_rate_warning = false;

	int slices = coreprof.array.rows();
	if (coreimpur.array.rows() != slices)
		throw std::invalid_argument("Number of cpo slices is different in coreprof and coreimpur.");
	if (equilibrium.array.rows() != slices)
		throw std::invalid_argument(
				"Number of cpo slices is different in coreprof and equilibrium.");

	for (int slice = 0; slice < slices; slice++) {

		if (coreprof[slice].time != coreimpur[slice].time
				|| coreprof[slice].time != equilibrium[slice].time)
			throw std::invalid_argument("Time value differs in cpo slices of the same index.");

		if (!critical_field_warning)
			critical_field_warning = is_field_critical(
					cpo_to_profile(coreprof[slice], coreimpur[slice], equilibrium[slice]));

		if (!growth_rate_warning)
			growth_rate_warning = is_growth_rate_over_limit(
					cpo_to_profile(coreprof[slice], coreimpur[slice], equilibrium[slice]),
					growth_rate_limit);
	}
}
