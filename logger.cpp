#include <iostream>
#include <string>

#include "logger.h"
#include "DynWS.h"

using namespace std;

void Logger::log(WL_LEVEL level, string message)
{
	cout << level << ": " << message << NEWLINE;
}

void Logger::Debug(string message)
{
	log(WL_DEBUG, message);
}

void Logger::Info(string message)
{
	log(WL_INFO, message);
}

void Logger::Error(string message)
{
	log(WL_ERROR, message);
}

void Logger::Fatal(string message)
{
	log(WL_FATAL, message);
}

void Logger::Con(string message)
{
	cout << message << NEWLINE;
}