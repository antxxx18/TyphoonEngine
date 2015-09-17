#include "stdafx.h"
#include "WinInputManager.h"
#include "WinInputCodes.h"
#include "InputSystem/InputListener.h"
#include "UtilSystem/Log.h"

namespace TE
{
	void WinInputManager::Init()
	{
		m_curWheel = m_curX = m_curY = 0;
		Log::Debug("InputMgr init");
	}

	void WinInputManager::Close()
	{
		if (!m_listenerList.empty())
			m_listenerList.clear();
		Log::Debug("InputMgr close");
	}

	void WinInputManager::SetWinRect(const RECT &winrect)
	{
		m_windowRect.left = winrect.left;
		m_windowRect.right = winrect.right;
		m_windowRect.top = winrect.top;
		m_windowRect.bottom = winrect.bottom;
	}

	void WinInputManager::AddListener(InputListener *Listener)
	{
		m_listenerList.push_back(Listener);
	}

	void WinInputManager::Run(UINT const & msg, WPARAM wParam, LPARAM lParam)
	{
		if (m_listenerList.empty())
			return;

		eKeyCodes KeyIndex;
		wchar_t buffer[1];
		BYTE lpKeyState[256];

		CursorEvent();
		switch (msg)
		{
		case WM_KEYDOWN:
			KeyIndex = static_cast<eKeyCodes>(wParam);
			GetKeyboardState(lpKeyState);
			ToUnicode(wParam, HIWORD(lParam) & 0xFF, lpKeyState, buffer, 1, 0);
			KeyEvent(KeyIndex, buffer[0], true);
			break;
		case WM_KEYUP:
			KeyIndex = static_cast<eKeyCodes>(wParam);
			GetKeyboardState(lpKeyState);
			ToUnicode(wParam, HIWORD(lParam) & 0xFF, lpKeyState, buffer, 1, 0);
			KeyEvent(KeyIndex, buffer[0], false);
			break;
		case WM_LBUTTONDOWN:
			MouseEvent(MOUSE_LEFT, true);
			break;
		case WM_LBUTTONUP:
			MouseEvent(MOUSE_LEFT, false);
			break;
		case WM_RBUTTONDOWN:
			MouseEvent(MOUSE_RIGHT, true);
			break;
		case WM_RBUTTONUP:
			MouseEvent(MOUSE_RIGHT, false);
			break;
		case WM_MBUTTONDOWN:
			MouseEvent(MOUSE_MIDDLE, true);
			break;
		case WM_MBUTTONUP:
			MouseEvent(MOUSE_MIDDLE, false);
			break;
		case WM_MOUSEWHEEL:
			MouseWheelEvent((short)GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
			break;
		}
	}

	void WinInputManager::CursorEvent()
	{
		POINT Position;
		GetCursorPos(&Position);

		Position.x -= m_windowRect.left;
		Position.y -= m_windowRect.top;

		if (Position.x < 0 || Position.y < 0)
			return;

		if (m_curX == Position.x && m_curY == Position.y)
			return;

		m_curX = Position.x;
		m_curY = Position.y;

		for (auto i : m_listenerList)
		{
			if (!i)
				continue;
			else if (i->IsMouseMove(Mouse(m_curX, m_curY)) == true)
				return;
		}
	}

	void WinInputManager::MouseEvent(const eMouseKeyCodes Code, bool press)
	{
		for (auto i : m_listenerList)
		{
			if (press == true)
			{
				if (i->IsMousePressed(MouseClick(Code, m_curX, m_curY)) == true)
					return;
			}
			else
			{
				if (i->IsMouseReleased(MouseClick(Code, m_curX, m_curY)) == true)
					return;
			}
		}
	}

	void WinInputManager::MouseWheelEvent(short Value)
	{
		if (m_curWheel == Value)
			return;

		m_curWheel = Value;

		for (auto i : m_listenerList)
		{
			if (i->IsMouseWheel(MouseWheel(m_curWheel, m_curX, m_curY)) == true)
				return;
		}
	}

	void WinInputManager::KeyEvent(const eKeyCodes KeyCode, const wchar_t ch, bool press)
	{
		for (auto i : m_listenerList)
		{
			if (press == true)
			{
				if (i->IsKeyPressed(Key(ch, KeyCode)) == true)
					return;
			}
			else
			{
				if (i->IsKeyReleased(Key(ch, KeyCode)) == true)
					return;
			}
		}
	}
}