#ifndef CPO_UTILS_H_
#define CPO_UTILS_H_

#include <UALClasses.h>
#include "plasma_structures.h"

bool equal(double a, double b, double tolerance);

int binary_search(const Array<double, 1> &array, double search_key);

double interpolate(const Array<double, 1> &x, const Array<double, 1> &y, double xa);

plasma_profile cpo_to_profile(const ItmNs::Itm::coreprof &coreprof, const ItmNs::Itm::coreimpur &coreimpur);	

#endif /* CPO_UTILS_H_ */
