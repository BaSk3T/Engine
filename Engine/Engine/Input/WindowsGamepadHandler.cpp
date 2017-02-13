#include "WindowsGamepadHandler.h"

#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")

#include "../DebugHelper.h"

// https://msdn.microsoft.com/en-us/library/windows/desktop/ee417001(v=vs.85).aspx

#define INPUT_DEADZONE (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)

WindowsGamepadHandler::WindowsGamepadHandler()
{
}

WindowsGamepadHandler::~WindowsGamepadHandler()
{
}

void WindowsGamepadHandler::HandleInput()
{
	DWORD dwResult;
	
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		HandleLeftStick(state);
		HandleRightStick(state);
	}
	else
	{
		// Controller is not connected 
	}
}

void WindowsGamepadHandler::HandleRightStick(XINPUT_STATE& state)
{
	float RX = state.Gamepad.sThumbRX;
	float RY = state.Gamepad.sThumbRY;

	//determine how far the controller is pushed
	float magnitude = sqrt(RX*RX + RY*RY);

	//determine the direction the controller is pushed
	float normalizedLX = RX / magnitude;
	float normalizedLY = RY / magnitude;

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > INPUT_DEADZONE)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= INPUT_DEADZONE;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - INPUT_DEADZONE);

		m_Gamepad.m_RightStickMagnitudeX = normalizedLX;
		m_Gamepad.m_RightStickMagnitudeY = normalizedLY;
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;

		m_Gamepad.m_RightStickMagnitudeX = 0.0f;
		m_Gamepad.m_RightStickMagnitudeY = 0.0f;
	}

	m_Gamepad.m_RightStickMagnitude = normalizedMagnitude;
}

void WindowsGamepadHandler::HandleLeftStick(XINPUT_STATE& state)
{
	float LX = state.Gamepad.sThumbLX;
	float LY = state.Gamepad.sThumbLY;

	//determine how far the controller is pushed
	float magnitude = sqrt(LX*LX + LY*LY);

	//determine the direction the controller is pushed
	float normalizedLX = LX / magnitude;
	float normalizedLY = LY / magnitude;

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > INPUT_DEADZONE)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= INPUT_DEADZONE;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - INPUT_DEADZONE);

		m_Gamepad.m_LeftStickMagnitudeX = normalizedLX;
		m_Gamepad.m_LeftStickMagnitudeY = normalizedLY;
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;

		m_Gamepad.m_LeftStickMagnitudeX = 0.0f;
		m_Gamepad.m_LeftStickMagnitudeY = 0.0f;
	}

	m_Gamepad.m_LeftStickMagnitude = normalizedMagnitude;
}
