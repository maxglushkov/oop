#pragma once

enum class Direction1D: signed char
{
	Backward = -1,
	Standstill,
	Forward
};

enum Sign: signed
{
	Minus = -1,
	Plus = 1
};

class Car
{
public:
	bool IsTurnedOn()const
	{
		return m_isEngineOn;
	}

	Direction1D GetDirection()const
	{
		if (m_speedProjection < 0)
		{
			return Direction1D::Backward;
		}
		if (m_speedProjection > 0)
		{
			return Direction1D::Forward;
		}
		return Direction1D::Standstill;
	}

	int GetSpeed()const
	{
		return m_speedProjection >= 0 ? m_speedProjection : -m_speedProjection;
	}

	int GetGear()const
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

	bool IsValidSpeedForGear(int speed, int gear)const
	{
		const int LOWER_BOUNDS[] = {0,  0,          0,  20, 30, 40, 50};
		const int UPPER_BOUNDS[] = {20, GetSpeed(), 30, 50, 60, 90, 150};
		if (gear < -1 || gear > 5)
		{
			return false;
		}
		++gear;
		return speed >= LOWER_BOUNDS[gear] && speed <= UPPER_BOUNDS[gear];
	}

protected:
	bool CanTurnOffEngine()const
	{
		return !m_gear && !m_speedProjection;
	}

	bool CanSetGear(int gear)const
	{
		if (!gear || gear == m_gear)
		{
			return true;
		}

		if (!m_isEngineOn)
		{
			return false;
		}

		if (gear < 0)
		{
			return m_speedProjection == 0;
		}
		return IsValidSpeedForGear(m_speedProjection, gear);
	}

	bool CanSetSpeed(int speed)const
	{
		return IsValidSpeedForGear(speed, m_gear);
	}

	Sign GetSpeedProjectionSign()const
	{
		if (m_gear < 0)
		{
			return Minus;
		}
		if (m_gear > 0)
		{
			return Plus;
		}
		return m_speedProjection >= 0 ? Plus : Minus;
	}

private:
	int m_gear = 0, m_speedProjection = 0;
	bool m_isEngineOn = false;
};
