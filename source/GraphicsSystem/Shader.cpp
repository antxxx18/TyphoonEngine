#include "stdafx.h"
#include "Shader.h"
#include "UtilSystem/Log.h"
#include "UtilSystem/Util.h"
#include "D3DDataTypes.h"

#define MAXLAYOUT 8

namespace TE
{
	Shader::Shader()
	{
		m_pVertexShader = nullptr;
		m_pPixelShader = nullptr;
		m_pLayout = nullptr;
		m_pLayoutFormat = nullptr;
		m_numLayout = 0;
	}

	void Shader::AddInputElementDesc(const char *SemanticName, DXGI_FORMAT format)
	{
		if (!m_numLayout)
		{
			m_pLayoutFormat = new D3D11_INPUT_ELEMENT_DESC[MAXLAYOUT];
			if (!m_pLayoutFormat)
				return;
		}
		else if (m_numLayout >= MAXLAYOUT)
			return;

		D3D11_INPUT_ELEMENT_DESC &Layout = m_pLayoutFormat[m_numLayout];

		Layout.SemanticName = SemanticName;
		Layout.SemanticIndex = 0;
		Layout.Format = format;
		Layout.InputSlot = 0;
		if (!m_numLayout)
			Layout.AlignedByteOffset = 0;
		else
			Layout.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		Layout.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		Layout.InstanceDataStepRate = 0;

		m_numLayout++;
	}

	void Shader::AddInputElementDesc(const char *SemanticName, unsigned int SemanticIndex, DXGI_FORMAT format, unsigned int InputSlot, bool AlignedByteOffset, D3D11_INPUT_CLASSIFICATION InputSlotClass, unsigned int InstanceDataStepRate)
	{
		if (!m_numLayout)
		{
			m_pLayoutFormat = new D3D11_INPUT_ELEMENT_DESC[MAXLAYOUT];
			if (!m_pLayoutFormat)
				return;
		}
		else if (m_numLayout >= MAXLAYOUT)
			return;

		D3D11_INPUT_ELEMENT_DESC &Layout = m_pLayoutFormat[m_numLayout];

		Layout.SemanticName = SemanticName;
		Layout.SemanticIndex = SemanticIndex;
		Layout.Format = format;
		Layout.InputSlot = InputSlot;
		if (!m_numLayout || !AlignedByteOffset)
			Layout.AlignedByteOffset = 0;
		else
			Layout.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		Layout.InputSlotClass = InputSlotClass;
		Layout.InstanceDataStepRate = InstanceDataStepRate;

		m_numLayout++;
	}

	bool Shader::CreateShader(wchar_t* namevs, wchar_t* nameps)
	{
		HRESULT hr = S_OK;
		ID3DBlob *vertexShaderBuffer = nullptr;
		hr = CompileShaderFromFile(namevs, "VS", "vs_4_0", &vertexShaderBuffer);
		if (FAILED(hr))
		{
			
			Log::Error("Could not load vetrex shader " + WCharToString(namevs));
			return false;
		}

		ID3DBlob *pixelShaderBuffer = nullptr;
		hr = CompileShaderFromFile(nameps, "PS", "ps_4_0", &pixelShaderBuffer);
		if (FAILED(hr))
		{
			Log::Error("Could not load vetrex shader " + WCharToString(nameps));
			return false;
		}

		hr = D3DDataTypes::GetD3DDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_pVertexShader);
		if (FAILED(hr))
		{
			Log::Error("Could not create vertex shader " + WCharToString(namevs));
			return false;
		}

		hr = D3DDataTypes::GetD3DDevice()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pPixelShader);
		if (FAILED(hr))
		{
			Log::Error("Could not create pixel shader " + WCharToString(nameps));
			return false;
		}

		hr = D3DDataTypes::GetD3DDevice()->CreateInputLayout(m_pLayoutFormat, m_numLayout, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_pLayout);
		if (FAILED(hr))
		{
			Log::Error("Could not create input layout.");
			return false;
		}
		_DeleteArray(m_pLayoutFormat);

		_Release(vertexShaderBuffer);
		_Release(pixelShaderBuffer);

		return true;
	}

	HRESULT Shader::CompileShaderFromFile(WCHAR* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel, ID3DBlob** ppBlobOut)
	{
		HRESULT hr = S_OK;

		DWORD ShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		ShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob *pErrorBlob = nullptr;
		hr = D3DX11CompileFromFile(FileName, NULL, NULL, EntryPoint, ShaderModel, ShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
		if (FAILED(hr) && pErrorBlob)
			Log::Error((char*)pErrorBlob->GetBufferPointer());

		_Release(pErrorBlob);
		return hr;
	}

	bool Shader::AddTexture(wchar_t* name)
	{
		ID3D11ShaderResourceView *texture = nullptr;
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile(D3DDataTypes::GetD3DDevice(), name, NULL, NULL, &texture, NULL);
		if (FAILED(hr))
		{
			Log::Error("Could not load texture " + WCharToString(name));
			return false;
		}

		m_textures.push_back(texture);

		return true;
	}

	void Shader::Draw()
	{
		D3DDataTypes::GetImmediateContext()->IASetInputLayout(m_pLayout);
		D3DDataTypes::GetImmediateContext()->VSSetShader(m_pVertexShader, NULL, 0);
		D3DDataTypes::GetImmediateContext()->PSSetShader(m_pPixelShader, NULL, 0);
		if (!m_textures.empty())
			D3DDataTypes::GetImmediateContext()->PSSetShaderResources(0, m_textures.size(), &m_textures[0]);
	}

	void Shader::Close()
	{
		_Release(m_pVertexShader);
		_Release(m_pPixelShader);
		_Release(m_pLayout);
		for (int i = 0; i < m_textures.size(); i++)
			_Release(m_textures[i]);
		m_textures.clear();
	}
}