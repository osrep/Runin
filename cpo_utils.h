#ifndef CPO_UTILS_H_
#define CPO_UTILS_H_

#include <UALClasses.h>
#include "cell.h"

bool equal(double a, double b, double tolerance);

int binary_search(const Array<double, 1> &array, double search_key);

double interpolate(const Array<double, 1> &x, const Array<double, 1> &y, double xa);

profile cpo_to_profile(const ItmNs::Itm::coreprof &coreprof, const ItmNs::Itm::coreimpur &coreimpur,
		const ItmNs::Itm::equilibrium &equilibrium);		
		
profile ids_to_profile(const IdsNs::IDS::core_profiles &core_profiles, const IdsNs::IDS::equilibrium &equilibrium, int timeindex);

#endif /* CPO_UTILS_H_ */
