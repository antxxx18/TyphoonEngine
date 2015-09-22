#include "stdafx.h"
#include "Core.h"
#include "CommonSystem/Common.h"
#include "UtilSystem/Log.h"

namespace TE
{
	Window* Core::m_pWindow = nullptr;
	Render* Core::m_pRender = nullptr;
	InputManager* Core::m_pInputManager = nullptr;
	Log* Core::m_pLog = nullptr;
	bool Core::m_isClosed = false;
	bool Core::m_isInit = false;
	IGame* Core::m_pGame = nullptr;


	Core::Core()
	{
		m_pLog = Log::Instance();
	}

	Core::~Core()
	{}

	bool Core::Init(EngineDesc const & desc)
	{
		m_pGame = desc.pGame;

		m_pWindow = new Window();
		m_pRender = new Render();
		m_pInputManager = new InputManager();

		m_pInputManager->Init();
		if (!m_pWindow->Create(desc.widnow))
		{
			Log::Error("Could not create window");
			return false;
		}
		m_pWindow->SetInputMgr(m_pInputManager);

		if (!m_pRender->CreateDevice(m_pWindow->GetHWND()))
		{
			Log::Error("Could not create render device");
			return false;
		}

		m_pGame->Init();

		m_isInit = true;
		return true;
	}

	void Core::AddInputListener(InputListener* pListener)
	{
		if (m_pInputManager)
			m_pInputManager->AddListener(pListener);
	}

	void Core::Run()
	{
		if (m_isInit)
			while (Frame());
	}

	bool Core::Frame()
	{
		m_pWindow->RunEvent();

		if (!m_pWindow->IsActive())
		{
			//return true;
		}

		if (m_pWindow->IsExit())
		{
			m_isClosed = true;
			return false;
		}

		if (m_isClosed)
			return false;

		if (m_pWindow->IsResize())
		{
		}

		m_pGame->Update();

		m_pRender->BeginFrame();
		m_pGame->Render();
		m_pRender->EndFrame();
		return true;
	}

	void Core::Close()
	{
		if (m_isClosed == false)
		{
			m_isClosed = true;
			return;
		}
		m_isInit = false;
		m_pRender->Shutdown();
		_Delete(m_pRender);
		_Close(m_pGame);
		_Close(m_pWindow);
		_Close(m_pInputManager);
		_Delete(m_pLog);
	}
}