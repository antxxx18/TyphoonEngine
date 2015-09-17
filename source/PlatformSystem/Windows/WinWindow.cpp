#include "stdafx.h"
#include "WinWindow.h"
#include "InputSystem/InputManager.h"
#include "UtilSystem/Log.h"

namespace TE
{
	WinWindow *WinWindow::m_wndthis = nullptr;

	WinWindow::WinWindow(void) :
		m_inputmgr(nullptr),
		m_hwnd(0),
		m_isExit(false),
		m_isActive(true),
		m_isMinimized(false),
		m_isMaximized(false),
		m_isResize(false)
	{
		if (!m_wndthis)
			m_wndthis = this;
		else
			Log::Error("Window already has been created");
	}

	bool WinWindow::Create(DescWindow const & desc)
	{
		Log::Debug("Window created");
		m_desc = desc;

		WNDCLASSEXW wnd;

		wnd.cbSize = sizeof(WNDCLASSEXW);
		wnd.style = CS_HREDRAW | CS_VREDRAW;
		wnd.lpfnWndProc = StaticWndProc;
		wnd.cbClsExtra = 0;
		wnd.cbWndExtra = 0;
		wnd.hInstance = 0;
		wnd.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wnd.hIconSm = wnd.hIcon;
		wnd.hCursor = LoadCursor(0, IDC_ARROW);
		wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wnd.lpszMenuName = NULL;
		wnd.lpszClassName = L"D3D11F";
		wnd.cbSize = sizeof(WNDCLASSEX);

		if (!RegisterClassEx(&wnd))
		{
			Log::Error("Could not create window");
			return false;
		}

		RECT rect = { 0, 0, m_desc.width, m_desc.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE);

		long lwidth = rect.right - rect.left;
		long lheight = rect.bottom - rect.top;

		long lleft = (long)m_desc.posX;
		long ltop = (long)m_desc.posY;

		m_hwnd = CreateWindowEx(NULL, L"D3D11F", m_desc.caption.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE, lleft, ltop, lwidth, lheight, NULL, NULL, NULL, NULL);

		if (!m_hwnd)
		{
			Log::Error("Could not create window");
			return false;
		}

		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);

		return true;
	}

	void WinWindow::RunEvent()
	{
		MSG msg;

		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WinWindow::Close()
	{
		if (m_hwnd)
			DestroyWindow(m_hwnd);
		m_hwnd = nullptr;

		Log::Debug("Window closed");
	}

	LRESULT WinWindow::WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (nMsg)
		{
		case WM_CREATE:
			return 0;
		case WM_CLOSE:
			m_isExit = true;
			return 0;
		case WM_ACTIVATE:
			if (LOWORD(wParam) != WA_INACTIVE)
				m_isActive = true;
			else
				m_isActive = false;
			return 0;
		case WM_MOVE:
			m_desc.posX = LOWORD(lParam);
			m_desc.posY = HIWORD(lParam);
			UpdateWindowState();
			return 0;
		case WM_SIZE:
			if (!m_desc.resizing)
				return 0;
			m_desc.width = LOWORD(lParam);
			m_desc.height = HIWORD(lParam);
			m_isResize = true;
			if (wParam == SIZE_MINIMIZED)
			{
				m_isActive = false;
				m_isMinimized = true;
				m_isMaximized = false;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				m_isActive = true;
				m_isMinimized = false;
				m_isMaximized = true;
			}
			else if (wParam == SIZE_RESTORED)
			{
				if (m_isMinimized)
				{
					m_isActive = true;
					m_isMinimized = false;
				}
				else if (m_isMaximized)
				{
					m_isActive = true;
					m_isMaximized = false;
				}
			}
			UpdateWindowState();
			return 0;
		case WM_MOUSEMOVE: case WM_LBUTTONUP: case WM_LBUTTONDOWN: case WM_MBUTTONUP: case WM_MBUTTONDOWN: case WM_RBUTTONUP: case WM_RBUTTONDOWN: case WM_MOUSEWHEEL: case WM_KEYDOWN: case WM_KEYUP:
			if (m_inputmgr)
				m_inputmgr->Run(nMsg, wParam, lParam);
			return 0;
		}

		return DefWindowProcW(hwnd, nMsg, wParam, lParam);
	}

	void WinWindow::SetInputMgr(InputManager *inputmgr)
	{
		m_inputmgr = inputmgr;
		UpdateWindowState();
	}

	void WinWindow::UpdateWindowState()
	{
		RECT ClientRect;
		ClientRect.left = m_desc.posX;
		ClientRect.top = m_desc.posY;
		ClientRect.right = m_desc.width;
		ClientRect.bottom = m_desc.height;
		if (m_inputmgr)
			m_inputmgr->SetWinRect(ClientRect);
	}

	LRESULT CALLBACK TE::StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
	{
		return WinWindow::Get()->WndProc(hwnd, nMsg, wParam, lParam);
	}
}