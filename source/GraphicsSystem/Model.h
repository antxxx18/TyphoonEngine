#pragma once

#include "Render.h"

namespace TE
{
	class Model
	{
	public:
		Model(Render* pRender);

		bool Init();
		void Draw(CXMMATRIX viewmatrix);
		void Close();

		void Translate(float x, float y, float z);
		void Rotate(float angle, float x, float y, float z);
		void Scale(float x, float y, float z);
		void Identity();

	//private:

		void RenderBuffers();
		void SetShaderParameters(CXMMATRIX viewmatrix);
		void RenderShader();

		Render* m_pRender;

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;
		ID3D11Buffer* m_pConstantBuffer;
		Shader* m_pShader;

		XMMATRIX m_objMatrix;
		unsigned short m_indexCount;
	};
}