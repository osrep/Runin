#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <UALClasses.h>
#include <libxml/xmlreader.h>
#include "DecodeITMpar.h"		
#include <unistd.h>
#include "H5Cpp.h"
#include "codeparams.h"
#include <stdlib.h>

using namespace std;

double get_rho_cutoff(ItmNs::codeparam_t &codeparams){

	double rho_max;
	DecITM::DecodeITMpar params(codeparams.parameters);
	std::string parameters;
	parameters = params.get();

	std::string str_rho_edge_calculation_limit = stream_xml_string(parameters, "rho_edge_calculation_limit");

	double dbl_rho_edge_calculation_limit = atof(str_rho_edge_calculation_limit.c_str());

	rho_max = dbl_rho_edge_calculation_limit;

	return rho_max;
}

double get_growth_rate_limit(ItmNs::codeparam_t &codeparams){

	double gr;
	DecITM::DecodeITMpar params(codeparams.parameters);
	std::string parameters;
	parameters = params.get();

	std::string str_growth_rate_limit = stream_xml_string(parameters, "growth_rate_limit");

	double dbl_growth_rate_limit = atof(str_growth_rate_limit.c_str());

	gr = dbl_growth_rate_limit;

	return gr;
}


std::string split_string(std::string s, std::string ref){

	std::string delimiter = "<";
	std::string delimiter2 = ">";
	std::string xml_value = ""; 
	size_t pos = 0;
	size_t pos2 = 0;
	std::string token, token2;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);

		for(int i=0; ((pos2 = token.find(delimiter2)) != std::string::npos);i++){
			token2 = token.substr(0, pos2);
			token.erase(0, pos2 + delimiter2.length());
			if (!token2.compare(ref)){
				std::cout <<"  [Runaway Indicator] \t Code Parameter for  "<<token2<<" is "<< token << std::endl;
				xml_value = token;
			}
		}

		s.erase(0, pos + delimiter.length());
	
	}

	return xml_value;

}



std::string stream_xml_string(std::string xml_string, std::string ref){

	return split_string(xml_string,ref);
}
