#include <stdexcept>
#include "cpo_utils.h"

bool equal(double a, double b, double tolerance) {
	return abs(a - b) * 2.0 > (a + b) * tolerance;
}

int binary_search(Array<double, 1> &array, int first, int last, double search_key) {
	if (first > last)
		return -1;

	int mid = (first + last) / 2;
	if (array(mid) <= search_key && search_key < array(mid + 1))
		return mid;

	if (search_key < array(mid))
		return binary_search(array, first, mid - 1, search_key);
	else
		return binary_search(array, mid + 1, last, search_key);
}

int binary_search(Array<double, 1> &array, double search_key) {
	return binary_search(array, 0, array.rows(), search_key);
}

double interpolate(Array<double, 1> &x, Array<double, 1> &y, double xa) {

	int rows = x.rows();
	if (rows != y.rows())
		throw std::invalid_argument("Number of rows is different in arrays to interpolate.");

	if (xa <= x(0))
		return y(0);
	if (xa >= x(x.rows()))
		return y(y.rows());

	int index = binary_search(x, xa);
	if (rows < 0)
		throw std::invalid_argument("Binary search failed.");

	return y(index) + (y(index + 1) - y(index)) / (x(index + 1) - x(index)) * (xa - x(index));
}

profile cpo_to_profile(ItmNs::Itm::coreprof &coreprof, ItmNs::Itm::coreimpur &coreimpur,
		ItmNs::Itm::equilibrium &equilibrium) {

	profile pro;

	int cells = coreprof.ne.value.rows();
	if (coreprof.te.value.rows() != cells)
		throw std::invalid_argument("Number of values is different in coreprof ne and te.");
	if (coreprof.profiles1d.e_b.value.rows() != cells)
		throw std::invalid_argument(
				"Number of values is different in coreprof.ne and profiles1d.e_b.");

	for (int rho = 0; rho < cells; rho++) {
		cell celll;
		celll.electron_density = coreprof.ne.value(rho);
		celll.electron_temperature = coreprof.te.value(rho);
		celll.electric_field = coreprof.profiles1d.e_b.value(rho)
				/ interpolate(equilibrium.profiles_1d.rho_tor, equilibrium.profiles_1d.b_av,
						coreprof.rho_tor(rho));
		celll.effective_charge = 0.0;

		for (int ion = 0; ion < coreprof.compositions.ions.rows(); ion++) {
			celll.effective_charge += coreprof.ni.value(rho, ion)
					* coreprof.compositions.ions(ion).zion * coreprof.compositions.ions(ion).zion;
		}

		for (int impurity = 0; impurity < coreimpur.impurity.rows(); impurity++) {

			for (int ionization_degree = 0;
					ionization_degree < coreimpur.impurity(impurity).z.extent(1);
					ionization_degree++) {

				Array<double, 1> density_profile = coreimpur.impurity(impurity).nz(Range::all(),
						ionization_degree);
				Array<double, 1> charge_profile = coreimpur.impurity(impurity).z(Range::all(),
						ionization_degree);

				double nz = interpolate(coreimpur.rho_tor, density_profile, coreprof.rho_tor(rho));
				double z = interpolate(coreimpur.rho_tor, charge_profile, coreprof.rho_tor(rho));

				celll.effective_charge += nz * z * z;
			}
		}

		// Assume sum of n_i * Z_i equals electron density because of quasi-neutrality
		celll.effective_charge /= celll.electron_density;

		pro.push_back(celll);
	}

	return pro;
}
