#pragma once

#include "InputSystem/InputManager.h"

namespace TE
{
	class InputMgr;

	struct DescWindow
	{
		DescWindow() :
			caption(L""),
			width(640),
			height(480),
			posX(200),
			posY(20),
			resizing(true)
		{}

		int posX;
		int posY;
		std::wstring caption;
		int width;
		int height;
		bool resizing;
	};

	class WinWindow
	{
	public:
		WinWindow();

		static WinWindow* Get() { return m_wndthis; }

		bool Create(const DescWindow& desc);

		void RunEvent();

		void Close();

		void SetInputMgr(InputManager* inputmgr);

		HWND GetHWND() const { return m_hwnd; }
		int WinWindow::GetLeft() const { return m_desc.posX; }
		int WinWindow::GetTop() const { return m_desc.posY; }
		int WinWindow::GetWidth() const { return m_desc.width; }
		int WinWindow::GetHeight() const { return m_desc.height; }

		std::wstring const & GetCaption() const { return m_desc.caption; }

		bool IsExit() const { return m_isExit; }

		bool IsActive() const { return m_isActive; }

		bool IsResize()
		{
			bool ret = m_isResize;
			m_isResize = false;
			return ret;
		}

		LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	private:
		void UpdateWindowState();

		static WinWindow* m_wndthis;

		DescWindow m_desc;
		InputManager* m_inputmgr;
		HWND m_hwnd;
		bool m_isExit;
		bool m_isActive;
		bool m_isMinimized;
		bool m_isMaximized;
		bool m_isResize;
	};

	static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
}