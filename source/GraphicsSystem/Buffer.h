#pragma once

namespace TE
{

	class Buffer
	{
	public:
		static ID3D11Buffer* CreateVertexBuffer(ID3D11Device* device, int size, bool dynamic, void const * Mem);
		static ID3D11Buffer* CreateIndexBuffer(ID3D11Device* device, int size, bool dynamic, void const * Mem);
		static ID3D11Buffer* CreateConstantBuffer(ID3D11Device* device, int size, bool dynamic);
	};

}