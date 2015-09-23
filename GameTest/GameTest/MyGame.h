#pragma once
#include <TEngine.h>
using namespace TE;

class MyGame : public IGame
{
public:
	MyGame(Core* core);
	~MyGame();

	void Init();
	void Update();
	void Render();
	void Close();

private:

	BitmapFont* font;
	Text* t1;

	Core* m_pCore;

	Model* model;
	Camera* camera;
};

