#pragma once

#include <TEngine.h>

using namespace TE;

class MyRender : public Render
{
public:
	MyRender();
	bool Init();
	bool Draw();
	void Close();

private:
	Model* model;
	XMMATRIX m_View;
};