#include "CameraInput.h"



CameraInput::CameraInput(Camera* pCamera)
{
	m_pCamera = pCamera;
}


CameraInput::~CameraInput()
{
}

bool CameraInput::IsKeyPressed(Key const & arg)
{
	if (arg.KeyCode == KEY_W)
		m_pCamera->MoveForward(true);
	if (arg.KeyCode == KEY_S)
		m_pCamera->MoveBackward(true);
	if (arg.KeyCode == KEY_A)
		m_pCamera->MoveLeft(true);
	if (arg.KeyCode == KEY_D)
		m_pCamera->MoveRight(true);
	return false;
}
