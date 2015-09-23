#pragma once

#include <TEngine.h>
using namespace TE;

class CameraInput : public InputListener
{
public:
	CameraInput(Camera* pCamera);
	~CameraInput();

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

	bool IsKeyPressed(Key const & arg);

	Camera* m_pCamera;
};

