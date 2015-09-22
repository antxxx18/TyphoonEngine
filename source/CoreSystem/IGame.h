#pragma once

namespace TE
{
	class IGame
	{
	public:
		IGame();
		virtual ~IGame();

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Close() = 0;
	};
}
