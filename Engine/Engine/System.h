#ifndef SYSTEM_H
#define SYSTEM_H

#include <Windows.h>

#include "Types.h"

class System
{
public:
	System();
	~System();

	UI32 Run();
	void InitializeWindow(UI32 width, UI32 height, HINSTANCE hInstance, int nCmdShow);

private:
	HWND m_hWnd;

	UI32 m_WindowWidth;
	UI32 m_WindowHeight;
};

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // !SYSTEM_H