#include "stdafx.h"
#include "D3DDataTypes.h"

namespace TE
{
	ID3D11Device* D3DDataTypes::m_pd3dDevice = nullptr;
	ID3D11DeviceContext*  D3DDataTypes::m_pImmediateContext = nullptr;
	IDXGISwapChain* D3DDataTypes::m_pSwapChain = nullptr;
}