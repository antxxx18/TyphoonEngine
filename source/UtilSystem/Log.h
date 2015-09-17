#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace TE
{
	class Log
	{
	public:
		static Log* Instance();
		static void Error(std::string msg);
		static void Info(std::string msg);
		static void Debug(std::string msg);
		~Log();

	private:
		Log();
		static void Print(std::string msgType, std::string msg);

		static Log* m_instance;
		static std::string m_fileName;
		static std::ofstream* m_fout;
	};
}