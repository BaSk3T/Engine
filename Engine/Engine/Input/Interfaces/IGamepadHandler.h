#ifndef IGAMEPADHANDLER_H
#define IGAMEPADHANDLER_H

struct Gamepad
{
	Gamepad() : m_LeftStickMagnitude(0),
		m_LeftStickMagnitudeX(0),
		m_LeftStickMagnitudeY(0),
		m_RightStickMagnitude(0),
		m_RightStickMagnitudeX(0),
		m_RightStickMagnitudeY(0) {};

	float m_LeftStickMagnitude;
	float m_LeftStickMagnitudeX;
	float m_LeftStickMagnitudeY;

	float m_RightStickMagnitude;
	float m_RightStickMagnitudeX;
	float m_RightStickMagnitudeY;
};

class IGamepadHandler
{
public:
	IGamepadHandler() {};
	virtual ~IGamepadHandler() {};

	Gamepad& GetGamepad() { return m_Gamepad; };

	virtual void HandleInput() = 0;


protected:
	Gamepad m_Gamepad;
};

#endif // !IGAMEPADHANDLER_H
