#include <catch2/catch.hpp>
#include "../car.h"

#define AND(first, second) ((first) ? (second) : false)

static bool TestGearLowerBound(Car & car, int gear, int lowerBound)
{
	return AND(
		AND(car.SetSpeed(lowerBound - 1), !car.SetGear(gear)),
		AND(car.SetSpeed(lowerBound), car.SetGear(gear))
	);
}

static bool TestGearUpperBound(Car & car, int gear, int upperBound)
{
	return AND(
		AND(car.SetGear(gear), car.SetSpeed(upperBound)),
		!car.SetSpeed(upperBound + 1)
	);
}

TEST_CASE("Default car state")
{
	Car car;
	REQUIRE(!car.IsTurnedOn());
	REQUIRE(car.GetDirection() == Direction1D::Standstill);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);
}

TEST_CASE("Manipulating car with engine turned off")
{
	Car car;
	REQUIRE(!car.SetGear(-1));
	REQUIRE(!car.SetGear(1));
	REQUIRE(car.GetGear() == 0);

	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(!car.SetSpeed(1));
	REQUIRE(car.GetDirection() == Direction1D::Standstill);
}

TEST_CASE("Upper speed bounds")
{
	Car car;
	REQUIRE(car.TurnOnEngine());
	REQUIRE(TestGearUpperBound(car, 0, 0));
	REQUIRE(TestGearUpperBound(car, 1, 30));
	REQUIRE(TestGearUpperBound(car, 2, 50));
	REQUIRE(TestGearUpperBound(car, 3, 60));
	REQUIRE(TestGearUpperBound(car, 4, 90));
	REQUIRE(TestGearUpperBound(car, 5, 150));
}

TEST_CASE("Lower speed bounds")
{
	Car car;
	REQUIRE(car.TurnOnEngine());

	REQUIRE(car.GetGear() == 0);
	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(car.GetDirection() == Direction1D::Standstill);

	REQUIRE(car.SetGear(1));
	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(car.GetDirection() == Direction1D::Standstill);

	REQUIRE(TestGearLowerBound(car, 2, 20));
	REQUIRE(TestGearLowerBound(car, 3, 30));
	REQUIRE(TestGearLowerBound(car, 4, 40));
	REQUIRE(TestGearLowerBound(car, 5, 50));
}

TEST_CASE("Turning off engine")
{
	Car car;
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.SetGear(1));
	REQUIRE(!car.TurnOffEngine());

	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.SetGear(0));
	REQUIRE(!car.TurnOffEngine());

	REQUIRE(!car.SetSpeed(21));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.TurnOffEngine());
}

TEST_CASE("Driving backwards")
{
	Car car;
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.SetGear(-1));
	REQUIRE(!car.TurnOffEngine());
	REQUIRE(car.SetSpeed(0));
	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(car.GetDirection() == Direction1D::Standstill);

	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.GetDirection() == Direction1D::Backward);
	REQUIRE(!car.SetSpeed(21));
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.SetGear(-1));
	REQUIRE(!car.SetGear(1));
	REQUIRE(car.SetGear(0));
	REQUIRE(!car.TurnOffEngine());

	REQUIRE(car.SetSpeed(1));
	REQUIRE(!car.SetGear(-1));
	REQUIRE(car.SetSpeed(1));
	REQUIRE(!car.SetSpeed(2));
	REQUIRE(car.GetSpeed() == 1);
	REQUIRE(car.GetDirection() == Direction1D::Backward);

	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.GetDirection() == Direction1D::Standstill);
	REQUIRE(!car.TurnOffEngine());
	REQUIRE(car.SetGear(0));
	REQUIRE(car.TurnOffEngine());
}
