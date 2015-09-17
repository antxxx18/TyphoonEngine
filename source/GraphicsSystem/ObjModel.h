#pragma once

#include "Render.h"

namespace TE
{
	class ObjModel
	{
	public:
		ObjModel(Render* pRender);

		bool Init();
		void Draw(CXMMATRIX view);
		bool Close();

		void Translate(float x, float y, float z);
		void Rotate(float angle, float x, float y, float z);
		void Scale(float x, float y, float z);
		void Identity();

		void* operator new(size_t i)
		{
			return _aligned_malloc(i,16);
		}

			void operator delete(void* p)
		{
			_aligned_free(p);
		}

	private:
		Render* m_pRender;
		
		bool LoadObjFile(wchar_t const * Filename);

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