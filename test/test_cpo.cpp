#include <gtest/gtest.h>
#include "../cpo_utils.h"
#include "../critical_field.h"
#include "../growth_rate.h"

const double reference_te = 1e5;
const double reference_ne = 1e21;
const double reference_growth_rate_1 = 8.27939e20;
const double reference_growth_rate_2 = 2.27479e21;
const double reference_Zeff_1 = 1.0;
const double reference_Zeff_2 = 1.2;
const double reference_electric_field_1 = 1.0;
const double reference_electric_field_2 = 1.2;

ItmNs::Itm::coreprof coreprof;
ItmNs::Itm::coreimpur coreimpur;

void create_cpo() {
	coreprof.rho_tor.resize(5);
	coreprof.rho_tor = 0.0, 1.0, 2.0, 4.0, 8.0;

	coreprof.ne.value.resize(5);
	coreprof.te.value.resize(5);
	coreprof.ne.value = 10.0, 11.0, 12.0, 14.0, 18.0;
	coreprof.te.value = 20.0, 21.0, 22.0, 24.0, 28.0;

	coreprof.toroid_field.b0 = 2.0;

	coreprof.profiles1d.eparallel.value.resize(5);
	coreprof.profiles1d.eparallel.value = 1.0, 2.0, 3.0, 5.0, 9.0;

	coreprof.ni.value.resize(5, 2);
	coreprof.ni.value = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

	coreprof.compositions.ions.resize(2);
	coreprof.compositions.ions(0).zion = 2.0;
	coreprof.compositions.ions(1).zion = 3.0;

	coreimpur.rho_tor.resize(6);
	coreimpur.rho_tor = 0.0, 1.0, 1.5, 2.0, 6.0, 10.0;

	coreimpur.impurity.resize(2);
	coreimpur.impurity(0).z.resize(6, 2);
	coreimpur.impurity(0).z = 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24;
	coreimpur.impurity(1).z.resize(6, 2);
	coreimpur.impurity(1).z = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12;

	coreimpur.impurity(0).nz.resize(6, 2);
	coreimpur.impurity(0).nz = 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2;
	coreimpur.impurity(1).nz.resize(6, 2);
	coreimpur.impurity(1).nz = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12;
}

TEST(CpoToProfil, ElectronDensity) {
	create_cpo();
	profile pro = cpo_to_profile(coreprof, coreimpur);

	ASSERT_EQ(5, pro.size());

	EXPECT_DOUBLE_EQ(10.0, pro[0].electron_density);
	EXPECT_DOUBLE_EQ(11.0, pro[1].electron_density);
	EXPECT_DOUBLE_EQ(12.0, pro[2].electron_density);
	EXPECT_DOUBLE_EQ(14.0, pro[3].electron_density);
	EXPECT_DOUBLE_EQ(18.0, pro[4].electron_density);
}

TEST(CpoToProfil, ElectronTemperature) {
	create_cpo();
	profile pro = cpo_to_profile(coreprof, coreimpur);

	ASSERT_EQ(5, pro.size());

	EXPECT_DOUBLE_EQ(20.0, pro[0].electron_temperature);
	EXPECT_DOUBLE_EQ(21.0, pro[1].electron_temperature);
	EXPECT_DOUBLE_EQ(22.0, pro[2].electron_temperature);
	EXPECT_DOUBLE_EQ(24.0, pro[3].electron_temperature);
	EXPECT_DOUBLE_EQ(28.0, pro[4].electron_temperature);
}

TEST(CpoToProfil, ElectricField) {
	create_cpo();
	profile pro = cpo_to_profile(coreprof, coreimpur);

	ASSERT_EQ(5, pro.size());

	EXPECT_DOUBLE_EQ(1.0, pro[0].electric_field);
	EXPECT_DOUBLE_EQ(2.0, pro[1].electric_field);
	EXPECT_DOUBLE_EQ(3.0, pro[2].electric_field);
	EXPECT_DOUBLE_EQ(5.0, pro[3].electric_field);
	EXPECT_DOUBLE_EQ(9.0, pro[4].electric_field);
}

TEST(CpoToProfil, EffectiveCharge) {
	create_cpo();
	profile pro = cpo_to_profile(coreprof, coreimpur);

	ASSERT_EQ(5, pro.size());

	EXPECT_NEAR(3.46000, pro[0].effective_charge, 0.00001);
	EXPECT_NEAR(131.24, pro[3].effective_charge, 0.01);
}
