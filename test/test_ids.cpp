#include <gtest/gtest.h>
#include "../cpo_utils.h"
#include "../ids_utils.h"

const double reference_te = 1e5;
const double reference_ne = 1e21;
const double reference_critical_field = 0.83625;
const double reference_growth_rate_1 = 8.27939e20;
const double reference_growth_rate_2 = 2.27479e21;
const double reference_Zeff_1 = 1.0;
const double reference_Zeff_2 = 1.2;
const double reference_electric_field_1 = 1.0;
const double reference_electric_field_2 = 1.2;

int timeindex = 0;

IdsNs::IDS::core_profiles core_profiles;
IdsNs::IDS::equilibrium equilibrium;

void create_ids() {
	core_profiles.rho_tor.resize(5);
	core_profiles.rho_tor = 0.0, 1.0, 2.0, 4.0, 8.0;

	core_profiles.ne.value.resize(5);
	core_profiles.te.value.resize(5);
	core_profiles.ne.value = 10.0, 11.0, 12.0, 14.0, 18.0;
	core_profiles.te.value = 20.0, 21.0, 22.0, 24.0, 28.0;

	core_profiles.toroid_field.b0 = 2.0;

	core_profiles.profiles1d.eparallel.value.resize(5);
	core_profiles.profiles1d.eparallel.value = 1.0, 2.0, 3.0, 5.0, 9.0;

	equilibrium.profiles_1d.rho_tor.resize(8);
	equilibrium.profiles_1d.rho_tor = 0.0, 1.0, 1.5, 2.0, 5.0, 10.0, 12.0, 15.0;
	equilibrium.profiles_1d.b_av.resize(8);
	equilibrium.profiles_1d.b_av = 5.5, 1.5, 5.5, 2.5, 1.6, 11.6, 15.5, 55.5;

	core_profiles.ni.value.resize(5, 2);
	core_profiles.ni.value = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

	core_profiles.compositions.ions.resize(2);
	core_profiles.compositions.ions(0).zion = 2.0;
	core_profiles.compositions.ions(1).zion = 3.0;
}

TEST(IdsToProfile, ElectronDensity) {
	create_ids();
	profile pro = ids_to_profile(core_profiles, equilibrium, timeindex);

	ASSERT_EQ(5, pro.size());

	EXPECT_DOUBLE_EQ(10.0, pro[0].electron_density);
	EXPECT_DOUBLE_EQ(11.0, pro[1].electron_density);
	EXPECT_DOUBLE_EQ(12.0, pro[2].electron_density);
	EXPECT_DOUBLE_EQ(14.0, pro[3].electron_density);
	EXPECT_DOUBLE_EQ(18.0, pro[4].electron_density);
}

TEST(IdsToProfile, ElectronTemperature) {
	create_ids();
	profile pro = ids_to_profile(core_profiles, equilibrium, timeindex);

	ASSERT_EQ(5, pro.size());

	EXPECT_DOUBLE_EQ(20.0, pro[0].electron_temperature);
	EXPECT_DOUBLE_EQ(21.0, pro[1].electron_temperature);
	EXPECT_DOUBLE_EQ(22.0, pro[2].electron_temperature);
	EXPECT_DOUBLE_EQ(24.0, pro[3].electron_temperature);
	EXPECT_DOUBLE_EQ(28.0, pro[4].electron_temperature);
}

TEST(IdsToProfile, ElectricField) {
	create_ids();
	profile pro = ids_to_profile(core_profiles, equilibrium, timeindex);

	ASSERT_EQ(5, pro.size());

	EXPECT_DOUBLE_EQ(1.0 * 2.0 / 5.5, pro[0].electric_field);
	EXPECT_DOUBLE_EQ(2.0 * 2.0 / 1.5, pro[1].electric_field);
	EXPECT_DOUBLE_EQ(3.0 * 2.0 / 2.5, pro[2].electric_field);
	EXPECT_DOUBLE_EQ(5.0 * 2.0 / 1.9, pro[3].electric_field);
	EXPECT_DOUBLE_EQ(9.0 * 2.0 / 7.6, pro[4].electric_field);
}

TEST(IdsToProfile, EffectiveCharge) {
	create_ids();
	profile pro = ids_to_profile(core_profiles, equilibrium, timeindex);

	ASSERT_EQ(5, pro.size());

	EXPECT_NEAR(3.46000, pro[0].effective_charge, 0.00001);
	EXPECT_NEAR(131.24, pro[3].effective_charge, 0.01);
}

TEST(CriticalField, IsFieldCritical) {
	cell cell1, cell2;

	cell1.electron_density = 0.9*reference_ne;
	cell1.electron_temperature = reference_te;
	cell1.electric_field = reference_critical_field;

	cell2.electron_density = 1.1*reference_ne;
	cell2.electron_temperature = reference_te;
	cell2.electric_field = reference_critical_field;

	profile pro;
	pro.push_back(cell1);
	EXPECT_EQ(1, is_field_critical(pro));

	pro.push_back(cell2);
	EXPECT_EQ(0, is_field_critical(pro));
}

TEST(GrowthRate, IsGrowthRateOverLimit) {
	cell cell1, cell2;

	cell1.electron_density = 0.9*reference_ne;
	cell1.electron_temperature = reference_te;
	cell1.effective_charge = reference_Zeff_1;
	cell1.electric_field = reference_electric_field_1;

	cell2.electron_density = 1.1*reference_ne;
	cell2.electron_temperature = reference_te;
	cell2.effective_charge = reference_Zeff_2;
	cell2.electric_field = reference_electric_field_2;

	profile pro;
	pro.push_back(cell1);
	EXPECT_EQ(1, is_growth_rate_over_limit(pro, reference_growth_rate_1));

	pro.push_back(cell2);
	EXPECT_EQ(0, is_growth_rate_over_limit(pro, reference_growth_rate_2));
}
