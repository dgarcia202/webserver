#include <iostream>
#include <string>

#include "logger.h"
#include "webserver.h"

using namespace std;

void logger::log(WL_LEVEL level, string message)
{
	cout << level << ": " << message << NEWLINE;
}

void logger::debug(string message)
{
	log(WL_DEBUG, message);
}

void logger::info(string message)
{
	log(WL_INFO, message);
}

void logger::error(string message)
{
	log(WL_ERROR, message);
}

void logger::fatal(string message)
{
	log(WL_FATAL, message);
}