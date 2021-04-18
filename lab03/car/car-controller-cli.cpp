#include <sstream>
#include "car-controller-cli.h"
using std::string;

CarControllerCli::Command CarControllerCli::PromptCommand(std::vector<std::string> & args)const
{
	m_output << "> ";
	args.clear();

	string cmdLine;
	if (!std::getline(m_input, cmdLine))
	{
		return Command::Quit;
	}

	Command cmd = Command::None;
	std::istringstream arguments(cmdLine);
	string argument;
	while (arguments >> argument)
	{
		if (cmd == Command::None)
		{
			if (argument == "Info")
			{
				cmd = Command::Info;
			}
			else if (argument == "EngineOn")
			{
				cmd = Command::EngineOn;
			}
			else if (argument == "EngineOff")
			{
				cmd = Command::EngineOff;
			}
			else if (argument == "SetGear")
			{
				cmd = Command::SetGear;
			}
			else if (argument == "SetSpeed")
			{
				cmd = Command::SetSpeed;
			}
			else
			{
				cmd = Command::Unknown;
			}
		}
		else
		{
			args.push_back(argument);
		}
	}
	return cmd;
}

CarControllerCli::Error CarControllerCli::ExecCommand(Command cmd, std::vector<std::string> const& args)const
{
	if (cmd != Command::Unknown)
	{
		if (args.size() != RequiredArgsCount(cmd))
		{
			return Error::InvalidArgumentsCount;
		}
	}

	try
	{
		switch (cmd)
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
				return SetGear(stoi(args[0]));
			case Command::SetSpeed:
				return SetSpeed(stoi(args[0]));
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
		if (gear < 0 && m_car.GetSpeed())
		{
			return Error::StillMoving;
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
