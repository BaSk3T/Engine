#ifndef CAMERA_H
#define CAMERA_H

#include <intrin.h>

#include <DirectXMath.h>

#include "../AlignedAllocationPolicy.h"

class Camera : public AlignedAllocationPoilicy<16>
{
public:
	Camera(float x, float y, float z);
	~Camera();

	void CalculateViewMatrix();
	DirectX::XMMATRIX GetViewMatrix() const { return m_ViewMatrix; };
	__m128 GetPosition() const { return m_Position; };

	void HandleInput(float leftStickX, float leftStickY, float rightStickX, float rightStickY);

private:
	void SetDefaultDirections();

	__m128 m_Position;
	DirectX::XMMATRIX m_ViewMatrix;

	float m_PositionXChange;
	float m_PositionZChange;

	float m_Pitch;	// rotation around X axis
	float m_Yaw;	// rotation around Y axis

	__m128 m_CameraDefaultForward;
	__m128 m_CameraDefaultRight;
	__m128 m_CameraDefaultUp;
};

#endif // !CAMERA_H
