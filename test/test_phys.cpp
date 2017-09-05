#include <gtest/gtest.h>
#include "../critical_field.h"
#include "../growth_rate.h"
#include "../cell.h"

const double reference_te = 1e5;
const double reference_ne = 1e21;
const double reference_dreicer_field = 17.452;
const double reference_critical_field = 0.83625;
const double reference_growth_rate_1 = 8.27939e20;
const double reference_growth_rate_2 = 2.27479e21;
const double reference_thermal_electron_collision_time = 4.9909e-4;
const double reference_Zeff_1 = 1.0;
const double reference_Zeff_2 = 1.2;
const double reference_electric_field_1 = 1.0;
const double reference_electric_field_2 = 1.2;

TEST(Equal, Tolerance) {
	EXPECT_TRUE(equal(1.0, 1.1, 0.1));
	EXPECT_TRUE(equal(-10.0, -11.0, 0.1));
	EXPECT_TRUE(equal(-10.0, 10.0, 2.0));
	EXPECT_FALSE(equal(1.0, 1.2, 0.1));
	EXPECT_FALSE(equal(-10.0, -12.0, 0.1));
}

TEST(BinarySearch, FindExistingValue) {
	blitz::Array<double, 1> ar(10);
	ar = 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
	EXPECT_EQ(0, binary_search(ar, 0.0));
	EXPECT_EQ(1, binary_search(ar, 1.0));
	EXPECT_EQ(2, binary_search(ar, 2.0));
	EXPECT_EQ(3, binary_search(ar, 3.0));
	EXPECT_EQ(4, binary_search(ar, 4.0));
	EXPECT_EQ(5, binary_search(ar, 5.0));
	EXPECT_EQ(6, binary_search(ar, 6.0));
	EXPECT_EQ(7, binary_search(ar, 7.0));
	EXPECT_EQ(8, binary_search(ar, 8.0));
	EXPECT_EQ(8, binary_search(ar, 9.0));
}

TEST(BinarySearch, FindValue) {
	blitz::Array<double, 1> ar(10);
	ar = 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
	EXPECT_EQ(0, binary_search(ar, 0.01));
	EXPECT_EQ(0, binary_search(ar, 0.99));
	EXPECT_EQ(1, binary_search(ar, 1.01));
	EXPECT_EQ(1, binary_search(ar, 1.99));
	EXPECT_EQ(6, binary_search(ar, 6.1));
	EXPECT_EQ(6, binary_search(ar, 6.5));
	EXPECT_EQ(7, binary_search(ar, 7.2));
	EXPECT_EQ(8, binary_search(ar, 8.01));
	EXPECT_EQ(8, binary_search(ar, 8.99));
}

TEST(Interpolate, Matching) {
	blitz::Array<double, 1> x(10), y(10);
	x = 0.0, 1.0, 2.0, 3.0, 4.0, 4.2, 4.6, 8.0, 8.5, 9.0;
	y = 0.0, 1.0, 2.0, 4.0, 8.0, 4.0, 2.0, 0.0, -2.0, 0.0;

	for (int i = 0; i < x.rows(); i++) {
		EXPECT_DOUBLE_EQ(y(i), interpolate(x, y, x(i)));
	}
}

TEST(Interpolate, Extrapolate) {
	blitz::Array<double, 1> x(10), y(10);
	x = 0.0, 1.0, 2.0, 3.0, 4.0, 4.2, 4.6, 8.0, 8.5, 9.0;
	y = 0.0, 1.0, 2.0, 4.0, 8.0, 4.0, 2.0, 0.0, -2.0, -1.0;
	EXPECT_DOUBLE_EQ(0.0, interpolate(x, y, -1.2));
	EXPECT_DOUBLE_EQ(0.0, interpolate(x, y, -100.2));
	EXPECT_DOUBLE_EQ(-1.0, interpolate(x, y, 9.1));
	EXPECT_DOUBLE_EQ(-1.0, interpolate(x, y, 900.1));

}

TEST(Interpolate, Intrapolate) {
	blitz::Array<double, 1> x(10), y(10);
	x = 0.0, 1.0, 2.0, 3.0, 4.0, 4.2, 4.6, 8.0, 8.5, 9.0;
	y = 0.0, 1.0, 2.0, 4.0, 8.0, 4.0, 2.0, 0.0, -2.0, 0.0;
	EXPECT_NEAR(0.5, interpolate(x, y, 0.5), 0.000001);
	EXPECT_NEAR(1.5, interpolate(x, y, 1.5), 0.000001);
	EXPECT_NEAR(3.0, interpolate(x, y, 2.5), 0.000001);
	EXPECT_NEAR(4.4, interpolate(x, y, 3.1), 0.000001);
	EXPECT_NEAR(7.6, interpolate(x, y, 3.9), 0.000001);
	EXPECT_NEAR(5.0, interpolate(x, y, 4.15), 0.000001);
	EXPECT_NEAR(3.75, interpolate(x, y, 4.25), 0.000001);
	EXPECT_NEAR(1.0, interpolate(x, y, 6.3), 0.000001);
	EXPECT_NEAR(-1.6, interpolate(x, y, 8.4), 0.000001);
	EXPECT_NEAR(-1.0, interpolate(x, y, 8.75), 0.000001);
}


TEST(CoulombLog, CalculateCoulombLog) {
	EXPECT_NEAR(16.4, calculate_coulomb_log(reference_ne, reference_te), 0.0001);
}

TEST(CriticalField, CalculateCriticalField) {
	EXPECT_NEAR(reference_critical_field, calculate_critical_field(reference_ne, reference_te), 0.0001);
}

TEST(GrowthRate, CalculateDreicerField) {
EXPECT_NEAR(reference_dreicer_field, calculate_dreicer_field(reference_thermal_electron_collision_time, reference_te), 0.01);
}

TEST(GrowthRate, CalculateThermalElectronCollisionTime) {
EXPECT_NEAR(reference_thermal_electron_collision_time, calculate_thermal_electron_collision_time(reference_ne,reference_te), 0.0001);
}

TEST(GrowthRate, CalculateGrowthRate_1) {
	EXPECT_NEAR(reference_growth_rate_1, calculate_growth_rate(reference_ne, reference_te, reference_Zeff_1, reference_electric_field_1), 1e18);
}

TEST(GrowthRate, CalculateGrowthRate_2) {
EXPECT_NEAR(reference_growth_rate_2, calculate_growth_rate(reference_ne, reference_te, reference_Zeff_2, reference_electric_field_2), 1e18);
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