#pragma once

#include "Render.h"

namespace TE
{
	class Shader
	{
	public:
		Shader(Render* pRender);
		void AddInputElementDesc(char const * SemanticName, DXGI_FORMAT format);
		void AddInputElementDesc(char const * SemanticName, unsigned int SemanticIndex, DXGI_FORMAT format, unsigned int InputSlot = 0, bool AlignedByteOffset = true, D3D11_INPUT_CLASSIFICATION InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, unsigned int InstanceDataStepRate = 0);

		bool CreateShader(wchar_t* namevs, wchar_t* nameps);
		bool AddTexture(wchar_t* name);

		void Draw();
		void Close();

	private:
		HRESULT CompileShaderFromFile(WCHAR* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel, ID3DBlob** ppBlobOut);

		Render* m_pRender;

		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;
		ID3D11InputLayout* m_pLayout;
		std::vector<ID3D11ShaderResourceView*> m_textures;
		D3D11_INPUT_ELEMENT_DESC* m_pLayoutFormat;
		unsigned int m_numLayout;
	};
}
