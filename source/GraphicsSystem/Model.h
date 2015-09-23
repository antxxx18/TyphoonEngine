#pragma once

#include "Render.h"
#include "Camera.h"
#include "Shader.h"

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

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;
		ID3D11Buffer* m_pConstantBuffer;
		Shader* m_pShader;

		unsigned short m_indexCount;

		void* operator new(size_t i)
		{
			return _aligned_malloc(i,16);
		}

			void operator delete(void* p)
		{
			_aligned_free(p);
		}

	private:

		void RenderBuffers();
		void SetShaderParameters(Camera* pCamera);
		void RenderShader();

		XMMATRIX m_objMatrix;
	};
}