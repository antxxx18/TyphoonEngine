#pragma once

namespace TE
{
	struct Vertex
	{
		XMFLOAT3 Pos;
		XMFLOAT2 Tex;
	};

	struct ConstantBuffer
	{
		XMMATRIX WVP;
	};
}