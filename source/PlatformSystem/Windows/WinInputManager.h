#pragma once

#include "WinInputCodes.h"

namespace TE
{
	class InputListener;

	class WinInputManager
	{
	public:
		void Init();
		void Close();

		void Run(UINT const & msg, WPARAM wParam, LPARAM lParam);

		void AddListener(InputListener* listener);

		void SetWinRect(RECT const & winRect);

	private:
		void CursorEvent();
		void MouseEvent(eMouseKeyCodes const KeyCode, bool press);
		void MouseWheelEvent(short Value);
		void KeyEvent(eKeyCodes const KeyCode, wchar_t const ch, bool press);

		std::list<InputListener*> m_listenerList;

		RECT m_windowRect;
		int m_curX;
		int m_curY;
		int m_curWheel;
	};
}