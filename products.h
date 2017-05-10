#ifndef PRODUCTS_H_
#define PRODUCTS_H_

#include <cmath>

//! 	\f[	m_\mathrm{e} \cdot c^2 \f]
double me_c2 = ITM_ME * pow(ITM_C, 2);

//! 	\f[	m_\mathrm{e}^2 \cdot c^3 \f]
double me2_c3 = me_c2 * ITM_ME * ITM_C;

//! 	\f[	\frac{m_\mathrm{e}^2 \cdot c^3}{e} \f]
double me2_c3__e = me2_c3 / ITM_QE;

//! 	\f[	\frac{4\pi\epsilon_0^2\cdot m_\mathrm{e}^2 c^3}{e^4} \f]
double pi_4_e02_me2_c3__e4 = ITM_PI * 4.0 * pow(ITM_EPS0, 2) * me2_c3 / pow(ITM_QE, 4);


//! 	\f[	\frac{4\pi\epsilon_0^2\cdot m_\mathrm{e}^2}{e^4} \f]
double pi_4_e02_me2__e4  = ITM_PI * 4.0 * pow(ITM_EPS0, 2) * ITM_ME *ITM_ME  / pow(ITM_QE, 4);

#endif /* PRODUCTS_H_ */
