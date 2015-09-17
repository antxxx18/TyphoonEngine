#include "stdafx.h"
#include "Log.h"

namespace TE
{
	Log* Log::m_instance = nullptr;
	std::string Log::m_fileName;
	std::ofstream* Log::m_fout;

	Log::~Log()
	{
		std::cout << "\n========================================\n";
		(*m_fout) << "\n========================================\n";
		Info("End of the log file!");
		m_fout->close();
		delete m_fout;
	}

	Log::Log()
	{

	}

	Log* Log::Instance()
	{
		if (m_instance == nullptr)
		{
			std::ios::sync_with_stdio(false);
			m_instance = new Log;
			m_fileName = "log.txt";
			m_fout = new std::ofstream(m_fileName);
			Info("Log was created!\n========================================\n");
		}
		return m_instance;
	}

	void Log::Error(std::string msg)
	{
		Print("Error", msg);
	}

	void Log::Info(std::string msg)
	{
		Print("Info", msg);
	}

	void Log::Debug(std::string msg)
	{
#ifdef _DEBUG
		Print("Debug", msg);
#endif // _DEBUG
	}

	void Log::Print(std::string msgType, std::string msg)
	{
		char timer[9];
		_strtime_s(timer, 9);
		clock_t cl = clock();
		std::cout << msgType << ": " << timer << "." << cl << " " << msg << std::endl;
		if (m_fout)
			(*m_fout) << msgType << ": " << timer << "." << cl << " " << msg << std::endl;
	}
}