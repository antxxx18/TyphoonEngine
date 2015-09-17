#pragma once

#include "GraphicsSystem/Window.h"
#include "GraphicsSystem/Render.h"
#include "InputSystem/InputManager.h"
#include "UtilSystem/Log.h"

namespace TE
{

	struct EngineDesc
	{
		DescWindow widnow;
		Render *render;
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

	private:
		static bool Frame();

		EngineDesc m_engineDesc;
		static Window* m_pWindow;
		static Render* m_pRender;
		static InputManager* m_pInputManager;
		static Log* m_pLog;
		static bool m_isInit;
		static bool m_isClosed;
	};
}