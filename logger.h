
#ifndef __LOGGER_H__
#define  __LOGGER_H__

using namespace std;

#include <string>

#define WL_DEBUG "DEBUG"
#define WL_INFO "INFO"
#define WL_ERROR "ERROR"
#define WL_FATAL "FATAL"

typedef string WL_LEVEL;

class Logger 
{

public:
	void Debug(string message);
	void Info(string message);
	void Error(string message);
	void Fatal(string message);
	void Con(string mwessage);

protected:
	void log(WL_LEVEL level, string message);
	
};

#endif