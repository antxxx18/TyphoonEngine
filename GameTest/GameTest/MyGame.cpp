#include "MyGame.h"
#include "CameraInput.h"

MyGame::MyGame(Core* core)
{
	m_pCore = core;
	camera = nullptr;
	model = nullptr;
	font = nullptr;
	t1 = nullptr;
}

MyGame::~MyGame()
{
}

void MyGame::Init()
{
	ModelLoader* ml = new ModelLoader();
	model = new Model();
	model->Init();
	ml->MS3DLoad(model, L"mesh.ms3d");
	_Delete(ml);

	camera = new Camera(0.4f*3.1415f, m_pCore->getRender()->GetWidth(), m_pCore->getRender()->GetHeight(), 0.01f, 1000.0f);
	camera->SetPos(0.0f, 2.0f, -2.8f);

	CameraInput* ci = new CameraInput(camera);
	m_pCore->AddInputListener(ci);

	font = new BitmapFont();
	font->Init("fontITALIC.fnt");

	t1 = new Text(font);
	t1->Init(L"Fps: 0", false, 20);
}

void MyGame::Update()
{
	static float sec = 1000;
	static float curt = 0;
	if (curt > sec)
	{
		std::wstring str(L"Fps: " + std::to_wstring((int)(1000.0f / Timer::GetTime())));
		t1->SetText(str);
		curt = 0;
	}
	curt += Timer::GetTime();
}

void MyGame::Render()
{

	camera->Render();
	model->Translate(0.0f, 0.0f, -2.0f);
	model->Draw(camera);
	model->Translate(0.0f, 0.0f, 2.0f);
	model->Draw(camera);
	t1->Draw(camera, 0.04, 1.0, 0.44, 10, 10);
}

void MyGame::Close()
{
	_Close(model);
}
