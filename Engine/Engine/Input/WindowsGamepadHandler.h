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
	void LeftStickMagnitude(XINPUT_STATE& state);
};

#endif // !WINDOWSGAMEPADHANDLER_H
