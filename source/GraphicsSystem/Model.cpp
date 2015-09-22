#include "stdafx.h"
#include "Model.h"
#include "Shader.h"
#include "GraphicUtil.h"
#include "D3DDataTypes.h"
#include "Camera.h"

namespace TE
{
	Model::Model()
	{
		m_pVertexBuffer = nullptr;
		m_pIndexBuffer = nullptr;
		m_pConstantBuffer = nullptr;
		m_pShader = nullptr;
	}

	bool Model::Init()
	{
		Identity();

		m_pShader = new Shader();
		if (!m_pShader)
			return false;

		m_pShader->AddInputElementDesc("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
		m_pShader->AddInputElementDesc("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
		if (!m_pShader->CreateShader(L"data/shaders/mesh.vs", L"data/shaders/mesh.ps"))
			return false;

		return true;
	}

	void Model::Draw(Camera* pCamera)
	{
		RenderBuffers();
		SetShaderParameters(pCamera);
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
		D3DDataTypes::GetImmediateContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
		D3DDataTypes::GetImmediateContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		D3DDataTypes::GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void Model::SetShaderParameters(Camera* pCamera)
	{
		XMMATRIX WVP = m_objMatrix * pCamera->GetViewMatrix() * pCamera->GetProjMatrix();
		ConstantBuffer cb;
		cb.WVP = XMMatrixTranspose(WVP);
		D3DDataTypes::GetImmediateContext()->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

		D3DDataTypes::GetImmediateContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	}

	void Model::RenderShader()
	{
		m_pShader->Draw();
		D3DDataTypes::GetImmediateContext()->DrawIndexed(m_indexCount, 0, 0);
	}

	
}