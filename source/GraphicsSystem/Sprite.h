#pragma once

#include "Render.h"

namespace TE
{
	class Sprite
	{
	public:
		Sprite(Render* pRender);

		bool Init(wchar_t* name, float bitmapWidth, float bitmapHeight);
		void Draw(float positionX, float positionY);
		void Close();

	private:
		bool InitBuffers();
		void RenderBuffers();
		void SetShaderParameters(float x, float y);
		void RenderShader();

		Render* m_pRender;

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;
		ID3D11Buffer* m_pConstantBuffer;
		Shader* m_pShader;

		float m_bitmapWidth, m_bitmapHeight;
		float m_previousPosX, m_previousPosY;
	};
}