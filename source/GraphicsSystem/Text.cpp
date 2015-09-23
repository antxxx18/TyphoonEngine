#include "stdafx.h"
#include "Text.h"
#include "Buffer.h"
#include "D3DDataTypes.h"

namespace TE
{
	Text::Text(BitmapFont* font)
	{
		m_font = font;
		m_vertexBuffer = nullptr;
		m_indexBuffer = nullptr;
		m_numindex = 0;
		m_numdrawindex = 0;
		m_numvertex = 0;
		m_isStatic = true;
		m_size = 0;
	}

	bool Text::Init(const std::wstring &text, bool statictext, int charsize)
	{
		m_isStatic = statictext;
		m_size = charsize;
		if (!m_InitBuffers(text))
			return false;

		return true;
	}

	bool Text::m_InitBuffers(const std::wstring &text)
	{
		if (!m_size || (m_size<text.size()))
			m_size = text.size();

		m_numvertex = m_size * 4;
		m_numindex = m_size * 6;
		m_numdrawindex = text.size() * 6;
		if (m_numdrawindex > m_numindex)
			m_numdrawindex = m_numindex;

		VertexFont *vertex = new VertexFont[m_numvertex];
		if (!vertex)
			return false;

		unsigned long *indices = new unsigned long[m_numindex];
		if (!indices)
			return false;

		m_font->BuildVertexArray(vertex, m_numvertex, text.c_str());

		for (int i = 0; i<m_numindex / 6; i++)
		{
			indices[i * 6 + 0] = i * 4 + 0;
			indices[i * 6 + 1] = i * 4 + 1;
			indices[i * 6 + 2] = i * 4 + 2;
			indices[i * 6 + 3] = i * 4 + 0;
			indices[i * 6 + 4] = i * 4 + 3;
			indices[i * 6 + 5] = i * 4 + 1;
		}

		m_vertexBuffer = Buffer::CreateVertexBuffer(D3DDataTypes::GetD3DDevice(), sizeof(VertexFont)*m_numvertex, !m_isStatic, vertex);
		if (!m_vertexBuffer)
			return false;

		m_indexBuffer = Buffer::CreateIndexBuffer(D3DDataTypes::GetD3DDevice(), sizeof(unsigned long)*m_numindex, false, indices);
		if (!m_indexBuffer)
			return false;

		_DeleteArray(vertex);
		_DeleteArray(indices);

		return true;
	}

	bool Text::m_updatebuffer(const std::wstring &text)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		HRESULT result = D3DDataTypes::GetImmediateContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
			return false;

		VertexFont *verticesPtr = (VertexFont*)mappedResource.pData;

		m_font->BuildVertexArray(verticesPtr, m_numvertex, text.c_str());

		D3DDataTypes::GetImmediateContext()->Unmap(m_vertexBuffer, 0);

		return true;
	}

	void Text::Draw(Camera* pCamera, float r, float g, float b, float x, float y)
	{
		m_RenderBuffers();
		m_font->Draw(pCamera, m_numdrawindex, r, g, b, x, y);
	}

	void Text::m_RenderBuffers()
	{
		unsigned int stride = sizeof(VertexFont);
		unsigned int offset = 0;
		D3DDataTypes::GetImmediateContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		D3DDataTypes::GetImmediateContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		D3DDataTypes::GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void Text::Close()
	{
		_Release(m_vertexBuffer);
		_Release(m_indexBuffer);
	}

	bool Text::SetText(const std::wstring &text)
	{
		if (m_isStatic)
			return false;
		m_numdrawindex = text.size() * 6;
		return m_updatebuffer(text);
	}
}