#include "stdafx.h"
#include "Render.h"
#include "CommonSystem/Common.h"
#include "UtilSystem/Log.h"
#include "Sprite.h"
#include "BitmapFont.h"
#include "Text.h"
#include "Model.h"
#include "D3DDataTypes.h"

namespace TE
{
	unsigned int Render::m_width = 0;
	unsigned int Render::m_height = 0;

	Render::Render()
	{
		m_pd3dDevice = nullptr;
		m_pImmediateContext = nullptr;
		m_pSwapChain = nullptr;
		m_pRenderTargetView = nullptr;
		m_pDepthStencilView = nullptr;
		m_pRenderState = nullptr;

		ClearColor[0] = 0.0f;
		ClearColor[1] = 0.0f;
		ClearColor[2] = 0.0f;
		ClearColor[3] = 1.0f;
	}

	Render::~Render()
	{}

	void Render::Resize()
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		m_width = rc.right - rc.left;
		m_height = rc.bottom - rc.top;
	}

	bool Render::CreateDevice(HWND hwnd)
	{
		m_hwnd = hwnd;

		Resize();

		if (!CreateDevice())
		{
			Log::Error("Could not create Direct3D device.");
			return false;
		}

		if (!CreateDepthStencil())
		{
			Log::Error("Could not create depth buffer.");
			return false;
		}

		m_pRenderState = new RenderState(m_pd3dDevice, m_pImmediateContext);

		if (!m_pRenderState->Init())
		{
			Log::Error("Could not create render state.");
			return false;
		}

		m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)m_width;
		vp.Height = (FLOAT)m_height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pImmediateContext->RSSetViewports(1, &vp);

		return true;
	}

	bool Render::CreateDevice()
	{
		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = m_width;
		sd.BufferDesc.Height = m_height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = m_hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, NULL, &m_pImmediateContext);
		if (FAILED(hr))
			return false;

		ID3D11Texture2D* pBackBuffer = nullptr;
		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if (FAILED(hr))
			return false;
		hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		_Release(pBackBuffer);
		if (FAILED(hr))
			return false;

		return true;
	}

	bool Render::CreateDepthStencil()
	{
		ID3D11Texture2D *m_pDepthStencil = nullptr;
		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory(&descDepth, sizeof(descDepth));
		descDepth.Width = m_width;
		descDepth.Height = m_height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		HRESULT hr = m_pd3dDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil);
		if (FAILED(hr))
			return false;

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		hr = m_pd3dDevice->CreateDepthStencilView(m_pDepthStencil, &descDSV, &m_pDepthStencilView);
		if (FAILED(hr))
			return false;

		_Release(m_pDepthStencil);

		D3DDataTypes::SetD3DDevice(m_pd3dDevice);
		D3DDataTypes::SetImmediateContext(m_pImmediateContext);
		D3DDataTypes::SetSwapChain(m_pSwapChain);

		return true;
	}

	void Render::SetClearColor(float r, float g, float b, float a)
	{
		ClearColor[0] = r;
		ClearColor[1] = g;
		ClearColor[2] = b;
		ClearColor[3] = a;
	}

	void Render::SetClearColor(float ClearColor[4])
	{
		for (int i = 0; i < 4; ++i)
			this->ClearColor[i] = ClearColor[i];
	}

	void Render::BeginFrame()
	{
		TurnZBufferOn();
		m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
		m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void Render::EndFrame()
	{
		m_pSwapChain->Present(0, 0);
	}

	void Render::Shutdown()
	{
		if (m_pImmediateContext)
			m_pImmediateContext->ClearState();;

		_Close(m_pRenderState);
		_Release(m_pDepthStencilView);
		_Release(m_pRenderTargetView);
		_Release(m_pSwapChain);
		_Release(m_pImmediateContext);
		_Release(m_pd3dDevice);
	}

	void Render::TurnZBufferOn()
	{
		m_pRenderState->TurnZBufferOn();
	}

	void Render::TurnZBufferOff()
	{
		m_pRenderState->TurnZBufferOff();
	}

	void Render::TurnOnAlphaBlending()
	{
		m_pRenderState->TurnOnAlphaBlending();
	}

	void Render::TurnOffAlphaBlending()
	{
		m_pRenderState->TurnOffAlphaBlending();
	}
}