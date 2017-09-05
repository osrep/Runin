#include <gtest/gtest.h>
#include "../ids_utils.h"
#include "../critical_field.h"
#include "../growth_rate.h"

const double reference_te = 1e5;
const double reference_ne = 1e21;
const double reference_critical_field = 0.83625;
const double reference_growth_rate_1 = 8.27939e20;
const double reference_growth_rate_2 = 2.27479e21;
const double reference_Zeff_1 = 1.0;
const double reference_Zeff_2 = 1.2;
const double reference_electric_field_1 = 1.0;
const double reference_electric_field_2 = 1.2;
const double reference_magnetic_field = 2.3;

int timeindex = 0;

IdsNs::IDS::core_profiles core_profiles;
IdsNs::IDS::equilibrium equilibrium;

void create_ids() {

    int N_rho = 5;
    core_profiles.profiles_1d(timeindex).grid.rho_tor_norm.resize(N_rho);
    core_profiles.profiles_1d(timeindex).grid.rho_tor_norm = 0.0, 0.1, 0.25, 0.40, 0.70;
    core_profiles.profiles_1d(timeindex).e_field.parallel.resize(N_rho);
    core_profiles.profiles_1d(timeindex).e_field.parallel = 1.0, 2.0, 3.0, 5.0, 9.0;

    core_profiles.profiles_1d(timeindex).electrons.density.resize(N_rho);
    core_profiles.profiles_1d(timeindex).electrons.density = 10.0, 11.0, 12.0, 14.0, 18.0;
    core_profiles.profiles_1d(timeindex).electrons.temperature.resize(N_rho);
    core_profiles.profiles_1d(timeindex).electrons.temperature = 20.0, 21.0, 22.0, 24.0, 28.0;
    core_profiles.profiles_1d(timeindex).zeff.resize(N_rho);
    core_profiles.profiles_1d(timeindex).zeff = 1.0, 1.3, 1.5, 1.75, 2.0;

    equilibrium.vacuum_toroidal_field.b0(timeindex) = reference_magnetic_field;
    equilibrium.time_slice(timeindex).profiles_1d.b_field_average.resize(N_rho);
    equilibrium.time_slice(timeindex).profiles_1d.b_field_average = 3.0, 2.4, 2.0, 1.75, 1.0;

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

	EXPECT_NEAR(1.0, pro[0].effective_charge, 0.01);
	EXPECT_NEAR(1.75, pro[3].effective_charge, 0.01);
}

