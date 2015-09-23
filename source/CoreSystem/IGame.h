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

		void* operator new(size_t i)
		{
			return _aligned_malloc(i,16);
		}

			void operator delete(void* p)
		{
			_aligned_free(p);
		}
	};
}
