#pragma once

#include "RenderState.h"

namespace TE
{
	class Render
	{
	public:
		Render();
		virtual ~Render();

		bool CreateDevice(HWND hwnd);
		void BeginFrame();
		void EndFrame();
		void Shutdown();
		void SetClearColor(float r, float g, float b, float a);
		void SetClearColor(float ClearColor[4]);

		void TurnZBufferOn();
		void TurnZBufferOff();

		void TurnOnAlphaBlending();
		void TurnOffAlphaBlending();

		void* operator new(size_t i)
		{
			return _aligned_malloc(i,16);
		}

			void operator delete(void* p)
		{
			_aligned_free(p);
		}

		static unsigned int GetWidth() { return m_width; }
		static unsigned int GetHeight() { return m_height; }

		XMMATRIX m_Ortho;
		XMMATRIX m_Projection;

	private:

		bool CreateDevice();
		bool CreateDepthStencil();
		void Resize();

		RenderState* m_pRenderState;

		float ClearColor[4];

		ID3D11Device* m_pd3dDevice;
		ID3D11DeviceContext* m_pImmediateContext;
		IDXGISwapChain* m_pSwapChain;
		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11DepthStencilView* m_pDepthStencilView;
		
		HWND m_hwnd;
		static unsigned int m_width;
		static unsigned int m_height;
	};
}