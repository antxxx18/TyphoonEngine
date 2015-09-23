#pragma once

namespace TE
{
	class Timer
	{
	public:
		bool Init();
		void Frame();

		static float GetTime();

	private:
		INT64 m_frequency;
		INT64 m_startTime;
		float m_ticksPerMs;
		static float m_frameTime;
	};
}