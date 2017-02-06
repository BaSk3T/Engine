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
	void InitializeWindow(HINSTANCE hInstance, int nCmdShow);

private:
	HWND m_hWnd;
};

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // !SYSTEM_H