#pragma once
#include <TEngine.h>
using namespace TE;

class MyGame : public IGame
{
public:
	MyGame();
	~MyGame();

	void Init();
	void Update();
	void Render();
	void Close();

private:
	Model* model;
	XMMATRIX m_View;
	Camera* camera;
};

