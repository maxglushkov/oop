#pragma once
#include <iostream>
#include <vector>
#include "car.h"

class CarControllerCli
{
public:
	enum class Command
	{
		Unknown = -1,
		None,
		Quit,
		Info,
		EngineOn,
		EngineOff,
		SetGear,
		SetSpeed
	};

	enum class Error
	{
		Unknown = -1,
		Success,
		InvalidCommand,
		InvalidArgumentsCount,
		InvalidArgument,
		EngineOff,
		StillMoving,
		GearIsSet,
		SpeedGearMismatch
	};

	CarControllerCli(Car & car, std::istream & input, std::ostream & output, std::ostream & error)
		:m_car(car)
		,m_input(input)
		,m_output(output)
		,m_error(error)
	{
	}

	Command PromptCommand(std::vector<std::string> & args)const;

	Error ExecCommand(Command cmd, std::vector<std::string> const& args)const;

	void PrintError(Error error)const
	{
		m_error << "Error: " << ErrorMessage(error) << '\n';
	}

protected:
	constexpr static size_t RequiredArgsCount(Command cmd)
	{
		switch (cmd)
		{
			case Command::SetGear:
			case Command::SetSpeed:
				return 1;
			default:
				return 0;
		}
	}

	constexpr static const char *ErrorMessage(Error error)
	{
		switch (error)
		{
			case Error::Success:
				return "success";
			case Error::InvalidCommand:
				return "invalid command";
			case Error::InvalidArgumentsCount:
				return "too few or too many arguments";
			case Error::InvalidArgument:
				return "invalid argument";
			case Error::EngineOff:
				return "the engine is off";
			case Error::StillMoving:
				return "the car is still moving";
			case Error::GearIsSet:
				return "the gear is set";
			case Error::SpeedGearMismatch:
				return "speed-gear mismatch";
			default:
				return "unknown error";
		}
	}

	Error Info()const;

	Error EngineOn()const;

	Error EngineOff()const;

	Error SetGear(int gear)const;

	Error SetSpeed(int speed)const;

	const char *IsTurnedOn()const
	{
		return m_car.IsTurnedOn() ? "on" : "off";
	}

	const char *GetDirection()const
	{
		switch (m_car.GetDirection())
		{
			case Direction1D::Backward:
				return "moving backward";
			case Direction1D::Standstill:
				return "not moving";
			case Direction1D::Forward:
				return "moving forward";
		}
		return nullptr;
	}

	char GetGear()const
	{
		switch (const int gear = m_car.GetGear())
		{
			case -1:
				return 'R';
			case 0:
				return 'N';
			default:
				return '0' + gear;
		}
	}

private:
	Car & m_car;
	std::istream & m_input;
	std::ostream & m_output, & m_error;
};
