#ifndef SYSTEM_H
#define SYSTEM_H

#include <Windows.h>

class Renderer;

#include <vector>

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

	std::vector<Renderer*> m_Renderers;
};

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // !SYSTEM_H