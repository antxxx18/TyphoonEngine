#pragma once
#include "stdafx.h"

namespace TE
{
	class D3DDataTypes
	{
	public:
		static ID3D11Device* GetD3DDevice(){ return m_pd3dDevice; }
		static ID3D11DeviceContext* GetImmediateContext() { return m_pImmediateContext; }
		static IDXGISwapChain* GetSwapChain() { return m_pSwapChain; }

		static void SetD3DDevice(ID3D11Device* pd3dDevice) { m_pd3dDevice = pd3dDevice; }
		static void SetImmediateContext(ID3D11DeviceContext* pImmediateContext) { m_pImmediateContext = pImmediateContext; }
		static void SetSwapChain(IDXGISwapChain* pSwapChain) { m_pSwapChain = pSwapChain; }

	private:
		static ID3D11Device* m_pd3dDevice;
		static ID3D11DeviceContext* m_pImmediateContext;
		static IDXGISwapChain* m_pSwapChain;
	};
}