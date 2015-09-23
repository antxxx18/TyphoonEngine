#pragma once

#include "Render.h"
#include "Camera.h"
#include "Shader.h"

namespace TE
{
	struct VertexFont
	{
		XMFLOAT3 pos;
		XMFLOAT2 tex;
	};

	class BitmapFont
	{
	private:
		struct CharDesc
		{
			CharDesc() : srcX(0), srcY(0), srcW(0), srcH(0), xOff(0), yOff(0), xAdv(0) {}

			short srcX;
			short srcY;
			short srcW;
			short srcH;
			short xOff;
			short yOff;
			short xAdv;
		};

		struct ConstantBuffer
		{
			XMMATRIX WVP;
		};
		struct PixelBufferType
		{
			XMFLOAT4 pixelColor;
		};
	public:
		BitmapFont();

		bool Init(char* fontFilename);
		void Draw(Camera* pCamera, unsigned int index, float r, float g, float b, float x, float y);
		void BuildVertexArray(VertexFont* vert, int numvert, wchar_t const * sentence);
		void Close();

	private:
		bool Parse(char* fontFilename);
		void SetShaderParameters(Camera* pCamera, float r, float g, float b, float x, float y);

		ID3D11Buffer* m_pConstantBuffer;
		ID3D11Buffer* m_pPixelBuffer;
		Shader* m_pShader;

		unsigned short m_WidthTex;
		unsigned short m_HeightTex;
		std::wstring m_file;
		std::map <int, CharDesc> m_Chars;
	};
}
