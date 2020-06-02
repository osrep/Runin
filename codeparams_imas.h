#ifndef CODEPARAMS_H_
#define CODEPARAMS_H_

#include <UALClasses.h>

double get_rho_cutoff(IdsNs::codeparam_t &codeparams);
double get_growth_rate_limit(IdsNs::codeparam_t &codeparams);

std::string stream_xml_string(std::string xml_string, std::string ref);
std::string split_string(std::string s, std::string ref);

#endif /* CODEPARAMS_H_ */
