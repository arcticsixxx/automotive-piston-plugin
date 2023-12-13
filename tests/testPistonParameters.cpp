#include "pch.h"

#include "../src/Core/PistonParameters.cpp"

namespace {
	// Tests for PistonParameters class

	// Test default constructor
	TEST(PistonParameters, DefaultConstructor)
	{
		// Arrange
		const PistonParameters pistonParameters;

		// Act
		const double value = pistonParameters.getValue(ParameterType::PistonHeight);

		// Assert
		EXPECT_EQ(value, 55.0f);
		EXPECT_TRUE(true);
	}

	// Tests setValue method positive
	TEST(PistonParameters, SetValuePositive)
	{
		// Arrange
		PistonParameters pistonParameters;

		// Act
		const bool result = pistonParameters.setValue(ParameterType::PistonHeight, 58.0f);

		// Assert
		EXPECT_TRUE(result);
	}

	// Tests the setValue method negative
	TEST(PistonParameters, SetValueNegative)
	{
		// Arrange
		PistonParameters pistonParameters;

		// Act
		const bool result = pistonParameters.setValue(ParameterType::PistonHeight, 35.0f);

		// Assert
		EXPECT_FALSE(result);
	}

	// Tests the getParameter method
	TEST(PistonParameters, GetParameter)
	{
		// Arrange
		const PistonParameters pistonParameters;

		// Act
		const double value = pistonParameters.getParameter(ParameterType::PistonHeight).getValue();

		// Assert
		EXPECT_EQ(value, 55.0f);
		EXPECT_TRUE(true);
	}
	
	// Tests the updateExtremums method
	TEST(PistonParameters, UpdateExtremums)
	{
		// Arrange
		PistonParameters pistonParameters;

		// Act
		pistonParameters.setValue(ParameterType::PistonHeight, 60);
		const double value = pistonParameters.getParameter(ParameterType::PistonHeadHeight).getMinValue();

		// Assert
		EXPECT_EQ(value, 15.0f);
		EXPECT_TRUE(true);
	}
}