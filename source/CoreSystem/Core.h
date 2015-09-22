#pragma once

#include "GraphicsSystem/Window.h"
#include "GraphicsSystem/Render.h"
#include "InputSystem/InputManager.h"
#include "UtilSystem/Log.h"
#include "IGame.h"

namespace TE
{

	struct EngineDesc
	{
		DescWindow widnow;
		IGame* pGame;
	};

	class Core
	{
	public:
		Core();
		~Core();

		bool Init(EngineDesc const & desc);
		void Run();
		static void Close();
		
		void AddInputListener(InputListener* pListener);

		static Render* getRender() { return m_pRender; }

	private:
		static bool Frame();

		EngineDesc m_engineDesc;
		static Window* m_pWindow;
		static Render* m_pRender;
		static InputManager* m_pInputManager;
		static Log* m_pLog;
		static bool m_isInit;
		static bool m_isClosed;
		static IGame* m_pGame;
	};
}