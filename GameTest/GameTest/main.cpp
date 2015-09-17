#include "TEngine.h"
#include <iostream>
#include "MyRender.h"
#include "MyInput.h"

using namespace TE;

/*
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
*/

int main()
{
	
	Core core;

	MyRender* render = new MyRender();
	MyInput* input = new MyInput(render);

	EngineDesc desc;
	//desc.widnow.resizing = false;
	desc.render = render;
	


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