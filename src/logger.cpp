#include <iostream>
#include <string>

#include "logger.h"

using namespace std;

namespace dynws 
{
	void Logger::log(WL_LEVEL level, string message)
	{
		cout << message << endl;
	}

	void Logger::logBytes(WL_LEVEL level, string message)
	{
		cout << message;
	}

	void Logger::debug(string message)
	{
		log(WL_DEBUG, message);
	}

	void Logger::debugBytes(string message)
	{
		logBytes(WL_DEBUG, message);
	}

	void Logger::info(string message)
	{
		log(WL_INFO, message);
	}

	void Logger::error(string message)
	{
		log(WL_ERROR, message);
	}

	void Logger::fatal(string message)
	{
		log(WL_FATAL, message);
	}

}	// namespace dynws