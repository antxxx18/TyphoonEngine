#include "stdafx.h"
#include "Model.h"
#include "Shader.h"
#include "GraphicUtil.h"

namespace TE
{


	Model::Model(Render* pRender)
	{
		m_pRender = pRender;
		m_pVertexBuffer = nullptr;
		m_pIndexBuffer = nullptr;
		m_pConstantBuffer = nullptr;
		m_pShader = nullptr;
	}

	bool Model::Init()
	{
		Identity();

		m_pShader = new Shader(m_pRender);
		if (!m_pShader)
			return false;

		m_pShader->AddInputElementDesc("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
		m_pShader->AddInputElementDesc("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
		if (!m_pShader->CreateShader(L"mesh.vs", L"mesh.ps"))
			return false;

		return true;
	}

	void Model::Draw(CXMMATRIX viewmatrix)
	{
		RenderBuffers();
		SetShaderParameters(viewmatrix);
		RenderShader();
	}

	void Model::Close()
	{
		_Release(m_pIndexBuffer);
		_Release(m_pVertexBuffer);
		_Release(m_pConstantBuffer);
		_Close(m_pShader);
	}

	void Model::Translate(float x, float y, float z)
	{
		m_objMatrix *= XMMatrixTranslation(x, y, z);
	}

	void Model::Rotate(float angle, float x, float y, float z)
	{
		XMVECTOR v = XMVectorSet(x, y, z, 0.0f);
		m_objMatrix *= XMMatrixRotationAxis(v, angle);
	}

	void Model::Scale(float x, float y, float z)
	{
		m_objMatrix *= XMMatrixScaling(x, y, z);
	}

	void Model::Identity()
	{
		m_objMatrix = XMMatrixIdentity();
	}

	void Model::RenderBuffers()
	{
		unsigned int stride = sizeof(Vertex);
		unsigned int offset = 0;
		m_pRender->m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
		m_pRender->m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		m_pRender->m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void Model::SetShaderParameters(CXMMATRIX viewmatrix)
	{
		XMMATRIX WVP = m_objMatrix * viewmatrix * m_pRender->m_Projection;
		ConstantBuffer cb;
		cb.WVP = XMMatrixTranspose(WVP);
		m_pRender->m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

		m_pRender->m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	}

	void Model::RenderShader()
	{
		m_pShader->Draw();
		m_pRender->m_pImmediateContext->DrawIndexed(m_indexCount, 0, 0);
	}

	
}