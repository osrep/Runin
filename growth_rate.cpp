#include <stdlib.h>
#include <cmath>
#include <vector>
#include <itm_constants.h>
#include "growth_rate.h"
#include "critical_field.h"

/*!

Growth rate warning

\details The module outputs an integer value (0 or 1) which indicates, whether the growth rate of runaway electron generation is above the limit value given in Demultiplexer workflow, thus runaway generation is to be expected. If the growth rate exceeds the limit value this warning raises.

\param pro profile
\param limit double


 4.2.3 Functional Requirements
\return REQ-1: If a radius exists where growth rate exceeds the limit, returns 1.
\return REQ-2: If growth rate is below limit across the whole profile, returns 0.
\return REQ-3: Growth rate is calculated
*/

int is_growth_rate_over_limit(profile pro, double limit) {
	//! maximal normalised minor radius
	double rho_max = 0.95;
	
	for (std::vector<cell>::iterator it = pro.begin(); it != pro.end(); ++it) {
		if ( (calculate_growth_rate(it->electron_density, it->electron_temperature,
				it->effective_charge, std::abs(it->electric_field)) > std::abs(limit))
				&& (it->rho < rho_max) )
			return 1;
	}

	return 0;
}

//! Calculation of growth rate
/*!
	\param electron_density \f$ n_\mathrm{e}\f$ electron density in \f$10^{20} \mathrm{~m}^{-3}\f$.
	\param electron_temperature \f$ t_\mathrm{e}\f$ electron temperature in \f$\mathrm{keV}\f$.
	\param effective_charge \f$ Z_\mathrm{eff} \f$ effective charge
	\param electric_field	\f$ E_\parallel \f$ electric field in \f$N/C\f$.
	
*/


double calculate_growth_rate(double electron_density, double electron_temperature,
		double effective_charge, double electric_field) {

	double coulomb_log = calculate_coulomb_log(electron_density, electron_temperature);

	/*! electron temperature
	\f[ T_\mathrm{e} \mathrm{[kJ]} = t_\mathrm{e} \mathrm{[keV]} \cdot e\f]
	*/
	
	//electron_temperature *= ITM_QE;

	//! \a REQ-3: diffusion time
	/*! 
	\f[
		\tau = 4 \pi \epsilon_0^2 \cdot \frac{m_\mathrm{e}^2 \cdot v^3 }{e^4} \cdot \frac{1}{n_\mathrm{e} \ln \Lambda}
	\f]
	*/

	double thermal_electron_collision_time = calculate_thermal_electron_collision_time(electron_density, electron_temperature);

	double dreicer_field = calculate_dreicer_field(thermal_electron_collision_time,electron_temperature);

	//! \return \a REQ-3: growth rate
		/*!
	\f[
		\dot{n}_r^I= \frac{n_\mathrm{e}}{\tau} \cdot \left(\frac{m_\mathrm{e} c^2}{2 T_\mathrm{e}} \right)^{3/2}\cdot
		\left( \frac{E_D}{E_\parallel}\right)^{3 \left(1+Z_\mathrm{eff}\right) / 16} \cdot 
		\exp \left( -\frac{E_D}{4E_\parallel} - \sqrt{(\frac{1+Z_\mathrm{eff}) \cdot E_D}{E_\parallel}}\right)
		
	\f]
	*/
	double me_c2 = ITM_ME * pow(ITM_C, 2);
	return electron_density / thermal_electron_collision_time * pow(me_c2 / (2.0 * electron_temperature*ITM_QE), 1.5)
			* pow(dreicer_field / electric_field, 3.0 * (1.0 + effective_charge) / 16.0)
			* exp(-dreicer_field / (4.0 * electric_field) - sqrt((1 + effective_charge) * dreicer_field / electric_field));
}
