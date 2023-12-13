#include "pch.h"

// official solution nuff said 
// https://learn.microsoft.com/en-us/visualstudio/test/how-to-use-google-test-for-cpp?view=vs-2022
#include "../src/Core/Parameter.cpp"

namespace {
	// Tests for Parameter class

	// Tests the default c'tor
	TEST(Parameter, DefaultConstructor)
	{
		// Arrange
		const Parameter parameter;

		// Act
		const double value = parameter.getValue();

		// Assert
		EXPECT_EQ(value, 0.0f);
		EXPECT_TRUE(true);
	}

	// Tests the c'tor that accepts values
	TEST(Parameter, ArgumentsConstructor)
	{
		// Arrange
		const Parameter parameter(10.0f, 5.0f, 20.0f);

		// Act
		const double value = parameter.getValue();
	
		// Assert
		EXPECT_EQ(value, 10.0f);
		EXPECT_TRUE(true);
	}

	// Tests the setValue method positive
	TEST(Parameter, SetValuePositive)
	{
		// Arrange
		Parameter parameter(9.0f, 8.0f, 15.0f);

		// Act
		const bool result = parameter.setValue(10.0f);

		// Assert
		EXPECT_EQ(parameter.getValue(), 10.0f);
		EXPECT_TRUE(result);
	}

	// Tests the setValue method negative
	TEST(Parameter, SetValueNegative)
	{
		// Arrange
		Parameter parameter(9.0f, 8.0f, 15.0f);

		// Act
		const bool result = parameter.setValue(6.0f);

		// Assert
		EXPECT_EQ(parameter.getValue(), 9.0f);
		EXPECT_FALSE(result);
	}

	// Tests the setMaxValue method
	TEST(Parameter, SetMaxValue)
	{
		// Arrange
		Parameter parameter;

		// Act
		parameter.setMaxValue(15.0f);

		// Assert
		EXPECT_EQ(parameter.getMaxValue(), 15.0f);
		EXPECT_TRUE(true);
	}

	// Tests the setMinValue method
	TEST(Parameter, SetMinValue)
	{
		// Arrange
		Parameter parameter;

		// Act
		parameter.setMinValue(5.0f);

		// Assert
		EXPECT_EQ(parameter.getMinValue(), 5.0f);
		EXPECT_TRUE(true);
	}

	// Test the getValue
	TEST(Parameter, GetValue)
	{
		// Arrange
		const Parameter parameter(9.0f, 8.0f, 15.0f);

		// Act
		const double value = parameter.getValue();

		// Assert
		EXPECT_EQ(value, 9.0f);
		EXPECT_TRUE(true);
	}

	// Test the getMaxValue
	TEST(Parameter, GetMaxValue)
	{
		// Arrange
		const Parameter parameter(9.0f, 8.0f, 15.0f);

		// Act
		const double maxValue = parameter.getMaxValue();

		// Assert
		EXPECT_EQ(maxValue, 15.0f);
		EXPECT_TRUE(true);
	}

	// Test the getMinValue
	TEST(Parameter, GetMinValue)
	{
		// Arrange
		const Parameter parameter(9.0f, 8.0f, 15.0f);

		// Act
		const double minValue = parameter.getMinValue();

		// Assert
		EXPECT_EQ(minValue, 8.0f);
		EXPECT_TRUE(true);
	}
}