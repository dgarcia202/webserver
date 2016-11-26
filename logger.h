
#ifndef __LOGGER_H__
#define  __LOGGER_H__

using namespace std;

#include <string>

#define WL_DEBUG "DEBUG"
#define WL_INFO "INFO"
#define WL_ERROR "ERROR"
#define WL_FATAL "FATAL"

typedef string WL_LEVEL;

class logger 
{
public:
	void debug(string message);
	void info(string message);
	void error(string message);
	void fatal(string message);

protected:
	void log(WL_LEVEL level, string message);
};

#endif