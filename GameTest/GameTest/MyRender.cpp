#include "MyRender.h"

MyRender::MyRender()
{
	model = nullptr;
}

bool MyRender::Init()
{
	ModelLoader* ml = new ModelLoader(this);
	model = new Model(this);
	ml->MS3DLoad(model, L"data/models/mesh.ms3d");

	XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, -2.8f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_View = XMMatrixLookAtLH(Eye, At, Up);
	return true;
}

bool MyRender::Draw()
{
	model->Draw(m_View);
	return true;
}

void MyRender::Close()
{
	
}