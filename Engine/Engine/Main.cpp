#include "System.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	System system;
	system.InitializeWindow(860, 640, hInstance, nCmdShow);
	UI32 message = system.Run();

	return message;
}