#include "MyInput.h"

MyInput::MyInput(MyRender *render)
{
	m_render = render;
}

bool MyInput::IsKeyPressed(const Key &arg)
{
	if (arg.KeyCode == KEY_UP)
		m_render->m_key_up = true;
	else if (arg.KeyCode == KEY_DOWN)
		m_render->m_key_down = true;
	else if (arg.KeyCode == KEY_LEFT)
		m_render->m_key_left = true;
	else if (arg.KeyCode == KEY_RIGHT)
		m_render->m_key_right = true;
	else if (arg.KeyCode == KEY_A)
		m_render->m_key_a = true;
	else if (arg.KeyCode == KEY_Z)
		m_render->m_key_z = true;
	else if (arg.KeyCode == KEY_S)
		m_render->m_key_s = true;
	else if (arg.KeyCode == KEY_X)
		m_render->m_key_x = true;

	return true;
}

bool MyInput::IsKeyReleased(const Key &arg)
{
	if (arg.KeyCode == KEY_UP)
		m_render->m_key_up = false;
	else if (arg.KeyCode == KEY_DOWN)
		m_render->m_key_down = false;
	else if (arg.KeyCode == KEY_LEFT)
		m_render->m_key_left = false;
	else if (arg.KeyCode == KEY_RIGHT)
		m_render->m_key_right = false;
	else if (arg.KeyCode == KEY_A)
		m_render->m_key_a = false;
	else if (arg.KeyCode == KEY_Z)
		m_render->m_key_z = false;
	else if (arg.KeyCode == KEY_S)
		m_render->m_key_s = false;
	else if (arg.KeyCode == KEY_X)
		m_render->m_key_x = false;

	return true;
}