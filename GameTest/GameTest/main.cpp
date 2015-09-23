#include <TEngine.h>
using namespace TE;
#include "MyGame.h"

class MyInput : public InputListener
{
public:
	bool IsMouseMove(Mouse const & arg)
	{
		std::string str = "mouse " + std::to_string(arg.x) + " - " + std::to_string(arg.y);
		Log::Info(str);
		return false;
	}

	bool IsMousePressed(MouseClick const & arg)
	{
		return false;
	}

	bool IsMouseReleased(MouseClick const & arg)
	{
		return false;
	}

	bool IsKeyPressed(Key const & arg)
	{
		if (arg.KeyCode == KEY_ESCAPE)
			Core::Close();
		return false;
	}
};


int main()
{
	Core core;

	MyGame* game = new MyGame(&core);
	MyInput* input = new MyInput();

	EngineDesc desc;
	//desc.widnow.resizing = false;
	desc.pGame = game;
	
	//desc.widnow.width = 800;
	//desc.widnow.height = 600;

	//desc.widnow.width = 1920;
	//desc.widnow.height = 1200;

	//desc.widnow.width = 1366;
	//desc.widnow.height = 768;

	core.Init(desc);
	core.AddInputListener(input);

	core.Run();
	core.Close();

	Sleep(1000);
	
	return 0;
}