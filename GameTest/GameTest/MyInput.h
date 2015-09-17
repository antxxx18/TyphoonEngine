#pragma once

#include <TEngine.h>
using namespace TE;
#include "MyRender.h"

class MyInput : public InputListener
{
public:
	MyInput(MyRender *render);

	bool IsKeyPressed(const Key &arg);
	bool IsKeyReleased(const Key &arg);

private:
	MyRender *m_render;
};