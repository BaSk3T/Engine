#ifndef IGAMEPADHANDLER_H
#define IGAMEPADHANDLER_H

struct Gamepad
{
	float m_LeftStickMagnitude;
	bool m_LeftStickIsRight;
	bool m_LeftStickIsUp;
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
