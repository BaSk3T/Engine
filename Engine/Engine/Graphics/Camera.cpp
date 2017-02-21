#include "Camera.h"

Camera::Camera(float x, float y, float z) :
	m_Pitch(0),
	m_Yaw(0),
	m_PositionXChange(0),
	m_PositionZChange(0),
	m_Position({x, y, z, 0})
{
	SetDefaultDirections();
}

Camera::~Camera()
{
}

void Camera::CalculateViewMatrix()
{
	DirectX::XMMATRIX cameraRotation = DirectX::XMMatrixRotationRollPitchYaw(m_Pitch, m_Yaw, 0);
	DirectX::XMVECTOR cameraTarget = DirectX::XMVector3Transform(m_CameraDefaultForward, cameraRotation);
	DirectX::XMVECTOR newForward = cameraTarget;
	cameraTarget = DirectX::XMVector3Normalize(cameraTarget);

	DirectX::XMVECTOR newRight = DirectX::XMVector3Transform(m_CameraDefaultRight, cameraRotation);
	DirectX::XMVECTOR newUp = DirectX::XMVector3Transform(m_CameraDefaultUp, cameraRotation);

	m_Position = DirectX::XMVectorAdd(m_Position, DirectX::XMVectorScale(newRight, m_PositionXChange));
	m_Position = DirectX::XMVectorAdd(m_Position, DirectX::XMVectorScale(newForward, m_PositionZChange));

	DirectX::XMVECTOR newTarget = DirectX::XMVectorSubtract(m_Position, cameraTarget);
	m_ViewMatrix = DirectX::XMMatrixLookAtRH(m_Position, newTarget, newUp);
}

void Camera::HandleInput(float leftStickX, float leftStickY, float rightStickX, float rightStickY)
{
	leftStickX /= 200;
	leftStickY /= 200;

	rightStickX /= 1000;
	rightStickY /= 1000;

	m_PositionXChange = leftStickX;
	m_PositionZChange = -leftStickY;

	m_Pitch += rightStickY;
	m_Yaw += -rightStickX;
}

void Camera::SetDefaultDirections()
{
	m_CameraDefaultForward = DirectX::XMVectorSet(0, 0, 1, 0);
	m_CameraDefaultRight = DirectX::XMVectorSet(1, 0, 0, 0);
	m_CameraDefaultUp = DirectX::XMVectorSet(0, 1, 0, 0);
}
