#pragma once

namespace TE
{
	struct Mouse
	{
		Mouse(int x, int y) : x(x), y(y) 
		{}

		int x;
		int y;
	};

	struct MouseClick : public Mouse
	{
		MouseClick(eMouseKeyCodes buttonCode, int x, int y) : Mouse(x, y), buttonCode(buttonCode) 
		{}

		const eMouseKeyCodes buttonCode;
	};

	struct MouseWheel : public Mouse
	{
		MouseWheel(int wheel, int x, int y) : Mouse(x, y), wheel(wheel) 
		{}

		int wheel;
	};

	struct Key
	{
		Key(wchar_t character, eKeyCodes KeyCode) : character(character), KeyCode(KeyCode) 
		{}

		const wchar_t character;
		const eKeyCodes KeyCode;
	};

	class InputListener
	{
	public:
		virtual bool IsMousePressed(const MouseClick &arg) { return false; }
		virtual bool IsMouseReleased(const MouseClick &arg) { return false; }
		virtual bool IsMouseWheel(const MouseWheel &arg) { return false; }
		virtual bool IsMouseMove(const Mouse &arg) { return false; }
		virtual bool IsKeyPressed(const Key &arg) { return false; }
		virtual bool IsKeyReleased(const Key &arg) { return false; }
	};
}