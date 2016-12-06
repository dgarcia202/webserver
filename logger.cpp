#include <iostream>
#include <string>

#include "logger.h"
#include "DynWS.h"

using namespace std;

void Logger::log(WL_LEVEL level, string message)
{
	cout << level << ": " << message << NEWLINE;
}

void Logger::debug(string message)
{
	log(WL_DEBUG, message);
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