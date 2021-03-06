#ifndef WINDOWSGAMEPADHANDLER_H
#define WINDOWSGAMEPADHANDLER_H

struct _XINPUT_STATE;
typedef _XINPUT_STATE XINPUT_STATE;

#include "Interfaces\IGamepadHandler.h"

class WindowsGamepadHandler : public IGamepadHandler
{
public:
	WindowsGamepadHandler();
	~WindowsGamepadHandler();

	virtual void HandleInput();

private:
	void HandleLeftStick(XINPUT_STATE& state);
	void HandleRightStick(XINPUT_STATE& state);
	void CalculateStickMagnitude(float x, float y, float& xMagnitude, float& yMagnitude, float& stickMagnitude);
};

#endif // !WINDOWSGAMEPADHANDLER_H
