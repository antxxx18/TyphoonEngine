#include "MyGame.h"

MyGame::MyGame()
{
	camera = nullptr;
	model = nullptr;
}

MyGame::~MyGame()
{
}

void MyGame::Init()
{
	ModelLoader* ml = new ModelLoader(Core::getRender());
	model = new Model();
	model->Init();
	ml->MS3DLoad(model, L"mesh.ms3d");
	_Delete(ml);

	camera = new Camera();
	camera->SetPos(0.0f, 0.0f, -2.8f);

	XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, -2.8f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_View = XMMatrixLookAtLH(Eye, At, Up);
}

void MyGame::Update()
{
}

void MyGame::Render()
{
	camera->Render();
	model->Draw(camera);
}

void MyGame::Close()
{
	_Close(model);
}
