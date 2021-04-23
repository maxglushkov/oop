#include <sstream>
#include "car-controller-cli.h"
using std::string;

void CarControllerCli::PromptCommand()
{
	m_output << "> ";

	string cmdLine;
	if (!std::getline(m_input, cmdLine))
	{
		m_command = Command::Quit;
		return;
	}

	std::istringstream arguments(cmdLine);
	string argument;
	while (arguments >> argument)
	{
		if (m_command == Command::None)
		{
			if (argument == "Info")
			{
				m_command = Command::Info;
			}
			else if (argument == "EngineOn")
			{
				m_command = Command::EngineOn;
			}
			else if (argument == "EngineOff")
			{
				m_command = Command::EngineOff;
			}
			else if (argument == "SetGear")
			{
				m_command = Command::SetGear;
			}
			else if (argument == "SetSpeed")
			{
				m_command = Command::SetSpeed;
			}
			else
			{
				m_command = Command::Unknown;
			}
		}
		else
		{
			m_arguments.push_back(argument);
		}
	}
}

CarControllerCli::Error CarControllerCli::ExecCommand()const
{
	if (m_command != Command::Unknown)
	{
		if (m_arguments.size() != RequiredArgsCount(m_command))
		{
			return Error::InvalidArgumentsCount;
		}
	}

	try
	{
		switch (m_command)
		{
			case Command::None:
				return Error::Success;
			case Command::Info:
				return Info();
			case Command::EngineOn:
				return EngineOn();
			case Command::EngineOff:
				return EngineOff();
			case Command::SetGear:
				return SetGear(stoi(m_arguments[0]));
			case Command::SetSpeed:
				return SetSpeed(stoi(m_arguments[0]));
			default:
				return Error::InvalidCommand;
		}
	}
	catch (std::exception e)
	{
		return Error::InvalidArgument;
	}
}

CarControllerCli::Error CarControllerCli::Info()const
{
	m_output << "The engine is " << IsTurnedOn() << '\n';
	m_output << "Car is " << GetDirection() << '\n';
	m_output << "Current gear is " << GetGear() << '\n';
	m_output << "Current speed is " << m_car.GetSpeed() << '\n';
	return Error::Success;
}

CarControllerCli::Error CarControllerCli::EngineOn()const
{
	if (!m_car.TurnOnEngine())
	{
		return Error::Unknown;
	}
	return Error::Success;
}

CarControllerCli::Error CarControllerCli::EngineOff()const
{
	if (!m_car.TurnOffEngine())
	{
		if (m_car.GetSpeed())
		{
			return Error::StillMoving;
		}
		if (m_car.GetGear())
		{
			return Error::GearIsSet;
		}
		return Error::Unknown;
	}
	return Error::Success;
}

CarControllerCli::Error CarControllerCli::SetGear(int gear)const
{
	if (!m_car.SetGear(gear))
	{
		if (gear < -1 || gear > 5)
		{
			return Error::InvalidArgument;
		}
		if (!m_car.IsTurnedOn())
		{
			return Error::EngineOff;
		}
		switch (gear)
		{
			case -1:
				if (m_car.GetSpeed())
				{
					return Error::StillMoving;
				}
				break;
			case 0:
				break;
			default:
				if (m_car.GetDirection() == Direction1D::Backward)
				{
					return Error::SpeedGearMismatch;
				}
		}
		if (!m_car.IsValidSpeedForGear(m_car.GetSpeed(), gear))
		{
			return Error::SpeedGearMismatch;
		}
		return Error::Unknown;
	}
	return Error::Success;
}

CarControllerCli::Error CarControllerCli::SetSpeed(int speed)const
{
	if (!m_car.SetSpeed(speed))
	{
		if (speed < 0)
		{
			return Error::InvalidArgument;
		}
		if (!m_car.IsValidSpeedForGear(speed, m_car.GetGear()))
		{
			return Error::SpeedGearMismatch;
		}
		return Error::Unknown;
	}
	return Error::Success;
}
