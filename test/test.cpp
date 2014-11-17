#include <gtest/gtest.h>
#include "../cpo_utils.h"

TEST(BinaryChearch, FindExistingValue) {
	blitz::Array<double, 1> ar(5);
	ar = 1.0, 2.0, 3.0, 4.0, 5.0;
	EXPECT_EQ(0, binary_search(ar, 1.0));
	EXPECT_EQ(1, binary_search(ar, 2.0));
	EXPECT_EQ(2, binary_search(ar, 3.0));
	EXPECT_EQ(4, binary_search(ar, 5.0));
}
