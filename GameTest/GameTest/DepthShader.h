#pragma once

#include <TEngine.h>
using namespace TE;

class MyRender;

class DepthShader
{
public:
	DepthShader(MyRender *render);

	bool Init();
	void Close();
	void Render(int, CXMMATRIX WVP);

private:
	MyRender *m_render;

	Shader *m_shader;
	ID3D11Buffer *m_matrixBuffer;
};