#ifndef CPO_UTILS_H_
#define CPO_UTILS_H_

#include <UALClasses.h>
#include "constants.h"

bool equal(double a, double b, double tolerance);

int binary_search(Array<double, 1> &array, double search_key);

double interpolate(Array<double, 1> &x, Array<double, 1> &y, double xa);

profile cpo_to_profile(ItmNs::Itm::coreprof &coreprof, ItmNs::Itm::coreimpur &coreimpur,
		ItmNs::Itm::equilibrium &equilibrium);

#endif /* CPO_UTILS_H_ */
