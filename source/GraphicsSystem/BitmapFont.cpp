#include "stdafx.h"
#include "BitmapFont.h"
#include "Buffer.h"
#include <fstream>
#include "Shader.h"
#include "UtilSystem/Util.h"
#include "D3DDataTypes.h"

namespace TE
{
	BitmapFont::BitmapFont()
	{
		m_pConstantBuffer = nullptr;
		m_pPixelBuffer = nullptr;
		m_pShader = nullptr;
		m_WidthTex = 0;
		m_HeightTex = 0;
	}

	bool BitmapFont::Init(char *fontFilename)
	{
		if (!Parse(fontFilename))
			return false;

		m_pShader = new Shader();
		if (!m_pShader)
			return false;

		if (!m_pShader->AddTexture((wchar_t*)m_file.c_str()))
			return false;
		m_pShader->AddInputElementDesc("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
		m_pShader->AddInputElementDesc("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);
		if (!m_pShader->CreateShader(L"data/shaders/BitmapFont.vs", L"data/shaders/BitmapFont.ps"))
			return false;


		m_pConstantBuffer = Buffer::CreateConstantBuffer(D3DDataTypes::GetD3DDevice(), sizeof(ConstantBuffer), false);
		if (!m_pConstantBuffer)
			return false;

		m_pPixelBuffer = Buffer::CreateConstantBuffer(D3DDataTypes::GetD3DDevice(), sizeof(PixelBufferType), false);
		if (!m_pPixelBuffer)
			return false;

		return true;
	}

	bool BitmapFont::Parse(char* fontFilename)
	{
		std::ifstream fin;
		fin.open(fontFilename);
		if (fin.fail())
			return false;

		std::string Line;
		std::string Read, Key, Value;
		size_t i;
		while (!fin.eof())
		{
			std::stringstream LineStream;
			std::getline(fin, Line);
			LineStream << Line;

			LineStream >> Read;
			if (Read == "common")
			{
				while (!LineStream.eof())
				{
					std::stringstream Converter;
					LineStream >> Read;
					i = Read.find('=');
					Key = Read.substr(0, i);
					Value = Read.substr(i + 1);

					Converter << Value;
					if (Key == "scaleW")
						Converter >> m_WidthTex;
					else if (Key == "scaleH")
						Converter >> m_HeightTex;
				}
			}
			else if (Read == "page")
			{
				while (!LineStream.eof())
				{
					std::stringstream Converter;
					LineStream >> Read;
					i = Read.find('=');
					Key = Read.substr(0, i);
					Value = Read.substr(i + 1);

					std::string str;
					Converter << Value;
					if (Key == "file")
					{
						Converter >> str;
						wchar_t *name = CharToWChar((char*)str.substr(1, Value.length() - 2).c_str());
						m_file = name;
						_DeleteArray(name);
					}
				}
			}
			else if (Read == "char")
			{
				unsigned short CharID = 0;
				CharDesc chard;

				while (!LineStream.eof())
				{
					std::stringstream Converter;
					LineStream >> Read;
					i = Read.find('=');
					Key = Read.substr(0, i);
					Value = Read.substr(i + 1);

					Converter << Value;
					if (Key == "id")
						Converter >> CharID;
					else if (Key == "x")
						Converter >> chard.srcX;
					else if (Key == "y")
						Converter >> chard.srcY;
					else if (Key == "width")
						Converter >> chard.srcW;
					else if (Key == "height")
						Converter >> chard.srcH;
					else if (Key == "xoffset")
						Converter >> chard.xOff;
					else if (Key == "yoffset")
						Converter >> chard.yOff;
					else if (Key == "xadvance")
						Converter >> chard.xAdv;
				}
				m_Chars.insert(std::pair<int, CharDesc>(CharID, chard));
			}
		}

		fin.close();

		return true;
	}

	void BitmapFont::BuildVertexArray(VertexFont *vertex, int numvert, const wchar_t *sentence)
	{
		int numLetters = (int)wcslen(sentence);
	
		if (numLetters * 4 > numvert)
			numLetters = numvert / 4;

		float drawX = (float)Render::GetWidth() / 2 * -1;
		float drawY = (float)Render::GetHeight() / 2;

		int index = 0;
		for (int i = 0; i<numLetters; i++)
		{
			float CharX = m_Chars[sentence[i]].srcX;
			float CharY = m_Chars[sentence[i]].srcY;
			float Width = m_Chars[sentence[i]].srcW;
			float Height = m_Chars[sentence[i]].srcH;
			float OffsetX = m_Chars[sentence[i]].xOff;
			float OffsetY = m_Chars[sentence[i]].yOff;

			float left = drawX + OffsetX;
			float right = left + Width;
			float top = drawY - OffsetY;
			float bottom = top - Height;
			float lefttex = CharX / m_WidthTex;
			float righttex = (CharX + Width) / m_WidthTex;
			float toptex = CharY / m_HeightTex;
			float bottomtex = (CharY + Height) / m_HeightTex;

			vertex[index].pos = XMFLOAT3(left, top, 0.0f);
			vertex[index].tex = XMFLOAT2(lefttex, toptex);
			index++;
			vertex[index].pos = XMFLOAT3(right, bottom, 0.0f);
			vertex[index].tex = XMFLOAT2(righttex, bottomtex);
			index++;
			vertex[index].pos = XMFLOAT3(left, bottom, 0.0f);
			vertex[index].tex = XMFLOAT2(lefttex, bottomtex);
			index++;
			vertex[index].pos = XMFLOAT3(right, top, 0.0f);
			vertex[index].tex = XMFLOAT2(righttex, toptex);
			index++;

			drawX += m_Chars[sentence[i]].xAdv;
		}
	}

	void BitmapFont::Draw(Camera* pCamera, unsigned int index, float r, float g, float b, float x, float y)
	{
		SetShaderParameters(pCamera, r, g, b, x, y);

		m_pShader->Draw();
		D3DDataTypes::GetImmediateContext()->DrawIndexed(index, 0, 0);
	}

	void BitmapFont::SetShaderParameters(Camera* pCamera, float r, float g, float b, float x, float y)
	{
		XMMATRIX objmatrix = XMMatrixTranslation(x, -y, 0);
		XMMATRIX wvp = objmatrix*pCamera->GetOrtoMatrix();
		ConstantBuffer cb;
		cb.WVP = XMMatrixTranspose(wvp);
		D3DDataTypes::GetImmediateContext()->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

		D3DDataTypes::GetImmediateContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

		PixelBufferType pb;
		pb.pixelColor = XMFLOAT4(r, g, b, 1.0f);
		D3DDataTypes::GetImmediateContext()->UpdateSubresource(m_pPixelBuffer, 0, NULL, &pb, 0, 0);

		D3DDataTypes::GetImmediateContext()->PSSetConstantBuffers(0, 1, &m_pPixelBuffer);
	}

	void BitmapFont::Close()
	{
		_Release(m_pConstantBuffer);
		_Release(m_pPixelBuffer);
		_Close(m_pShader);
	}
}