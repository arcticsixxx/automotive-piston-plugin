#include "pch.h"

#include "../src/Core/Validator.cpp"

namespace {
	// Tests for validator class

	// Tests Validate method positive
	TEST(Validator, ValidatePositive)
	{
		// Arrange 
		constexpr double value = 10.0f;
		constexpr double minValue = 5.0f;
		constexpr double maxValue = 15.0f;

		// Act
		const bool result = Validator::ValidateParameter(value, minValue, maxValue);

		// Assert
		EXPECT_TRUE(result);
	}

	// Tests Validate method positive
	TEST(Validator, ValidateNegative)
	{
		// Arrange 
		constexpr double value = 10.0f;
		constexpr double minValue = 12.0f;
		constexpr double maxValue = 15.0f;

		// Act
		const bool result = Validator::ValidateParameter(value, minValue, maxValue);

		// Assert
		EXPECT_FALSE(result);
	}
}