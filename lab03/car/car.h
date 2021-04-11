#pragma once

enum class Direction1D: signed char
{
	Backward = -1,
	None,
	Forward
};

class Car
{
public:
	bool IsTurnedOn()
	{
		return m_isEngineOn;
	}

	Direction1D GetDirection()
	{
		if (m_speedProjection < 0)
		{
			return Direction1D::Backward;
		}
		if (m_speedProjection > 0)
		{
			return Direction1D::Forward;
		}
		return Direction1D::None;
	}

	int GetSpeed()
	{
		return m_speedProjection < 0 ? -m_speedProjection : m_speedProjection;
	}

	int GetGear()
	{
		return m_gear;
	}

	bool TurnOnEngine()
	{
		m_isEngineOn = true;
		return true;
	}

	bool TurnOffEngine()
	{
		if (!CanTurnOffEngine())
		{
			return false;
		}

		m_isEngineOn = false;
		return true;
	}

	bool SetGear(int gear)
	{
		if (!CanSetGear(gear))
		{
			return false;
		}

		m_gear = gear;
		return true;
	}

	bool SetSpeed(int speed)
	{
		if (!CanSetSpeed(speed))
		{
			return false;
		}

		m_speedProjection = GetSpeedProjectionSign() * speed;
		return true;
	}

protected:
	bool CanTurnOffEngine()
	{
		return !m_gear && !m_speedProjection;
	}

	bool CanSetGear(int gear)
	{
		if (!gear || gear == m_gear)
		{
			return true;
		}

		if (!m_isEngineOn)
		{
			return false;
		}

		if (gear == -1)
		{
			return m_speedProjection == 0;
		}
		return IsValidSpeedForGear(m_speedProjection, gear);
	}

	bool CanSetSpeed(int speed)
	{
		if (!m_gear)
		{
			return speed >= 0 ? speed <= GetSpeed() : false;
		}
		return IsValidSpeedForGear(speed, m_gear);
	}

	int GetSpeedProjectionSign()
	{
		if (m_gear < 0)
		{
			return -1;
		}
		if (m_gear > 0)
		{
			return 1;
		}
		return m_speedProjection >= 0 ? 1 : -1;
	}

	static bool IsValidSpeedForGear(int speed, int gear)
	{
		if (speed < 0)
		{
			return false;
		}

		switch (gear)
		{
			case -1:
				return speed <= 20;
			case 0:
				return true;
			case 1:
				return speed <= 30;
			case 2:
				return speed >= 20 && speed <= 50;
			case 3:
				return speed >= 30 && speed <= 60;
			case 4:
				return speed >= 40 && speed <= 90;
			case 5:
				return speed >= 50 && speed <= 150;
			default:
				return false;
		}
	}

private:
	int m_gear = 0, m_speedProjection = 0;
	bool m_isEngineOn = false;
};
