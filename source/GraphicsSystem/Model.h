#pragma once

#include "Render.h"
#include "Camera.h"

namespace TE
{
	class Model
	{
	public:
		Model();

		bool Init();
		void Draw(Camera* pCamera);
		void Close();

		void Translate(float x, float y, float z);
		void Rotate(float angle, float x, float y, float z);
		void Scale(float x, float y, float z);
		void Identity();

	//private:

		void RenderBuffers();
		void SetShaderParameters(Camera* pCamera);
		void RenderShader();

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;
		ID3D11Buffer* m_pConstantBuffer;
		Shader* m_pShader;

		XMMATRIX m_objMatrix;
		unsigned short m_indexCount;
	};
}