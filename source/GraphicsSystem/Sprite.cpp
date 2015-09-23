#include "stdafx.h"
#include "Sprite.h"
#include "Shader.h"
#include "UtilSystem/Log.h"
#include "Buffer.h"
#include "D3DDataTypes.h"

namespace TE
{
	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT2 tex;
	};

	struct ConstantBuffer
	{
		XMMATRIX Ortho;
	};

	Sprite::Sprite()
	{
		m_pVertexBuffer = nullptr;
		m_pIndexBuffer = nullptr;
		m_pConstantBuffer = nullptr;
		m_pShader = nullptr;
	}

	bool Sprite::Init(wchar_t* textureFilename, float bitmapWidth, float bitmapHeight)
	{
		m_bitmapWidth = bitmapWidth;
		m_bitmapHeight = bitmapHeight;
		m_previousPosX = -1;
		m_previousPosY = -1;

		if (!InitBuffers())
			return false;

		m_pShader = new Shader();
		if (!m_pShader)
			return false;
		if (!m_pShader->AddTexture(textureFilename))
			return false;
		m_pShader->AddInputElementDesc("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
		m_pShader->AddInputElementDesc("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
		if (!m_pShader->CreateShader(L"image.vs", L"image.ps"))
			return false;

		return true;
	}

	bool Sprite::InitBuffers()
	{
		Vertex vertices[4];

		signed int centreW = Render::GetWidth() / 2 * -1;
		signed int centreH = Render::GetHeight() / 2;
		float left = (float)centreW;
		float right = left + m_bitmapWidth;
		float top = (float)centreH;
		float bottom = top - m_bitmapHeight;

		vertices[0].pos = XMFLOAT3(left, top, 0.0f);
		vertices[0].tex = XMFLOAT2(0.0f, 0.0f);

		vertices[1].pos = XMFLOAT3(right, bottom, 0.0f);
		vertices[1].tex = XMFLOAT2(1.0f, 1.0f);

		vertices[2].pos = XMFLOAT3(left, bottom, 0.0f);
		vertices[2].tex = XMFLOAT2(0.0f, 1.0f);

		vertices[3].pos = XMFLOAT3(right, top, 0.0f);
		vertices[3].tex = XMFLOAT2(1.0f, 0.0f);

		unsigned long indices[6] =
		{
			0,1,2,
			0,3,1
		};

		m_pVertexBuffer = Buffer::CreateVertexBuffer(D3DDataTypes::GetD3DDevice(), sizeof(Vertex) * 4, false, &vertices);
		if (!m_pVertexBuffer)
			return false;

		m_pIndexBuffer = Buffer::CreateIndexBuffer(D3DDataTypes::GetD3DDevice(), sizeof(unsigned long) * 6, false, &indices);
		if (!m_pIndexBuffer)
			return false;

		m_pConstantBuffer = Buffer::CreateConstantBuffer(D3DDataTypes::GetD3DDevice(), sizeof(ConstantBuffer), false);
		if (!m_pConstantBuffer)
			return false;

		return true;
	}

	void Sprite::Draw(Camera* pCamera, float positionX, float positionY)
	{
		RenderBuffers();
		SetShaderParameters(pCamera, positionX, positionY);
		RenderShader();
	}

	void Sprite::RenderBuffers()
	{
		unsigned int stride = sizeof(Vertex);
		unsigned int offset = 0;
		D3DDataTypes::GetImmediateContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
		D3DDataTypes::GetImmediateContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		D3DDataTypes::GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void Sprite::SetShaderParameters(Camera* pCamera, float x, float y)
	{
		XMMATRIX objmatrix = XMMatrixTranslation(x, -y, 0.0f);
		XMMATRIX wvp = objmatrix*pCamera->GetProjMatrix();
		ConstantBuffer cb;
		cb.Ortho = XMMatrixTranspose(wvp);
		D3DDataTypes::GetImmediateContext()->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

		D3DDataTypes::GetImmediateContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	}

	void Sprite::RenderShader()
	{
		m_pShader->Draw();
		D3DDataTypes::GetImmediateContext()->DrawIndexed(6, 0, 0);
	}

	void Sprite::Close()
	{
		_Release(m_pVertexBuffer);
		_Release(m_pIndexBuffer);
		_Release(m_pConstantBuffer);
		_Close(m_pShader);
	}
}