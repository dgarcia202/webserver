
#ifndef __DYNWS_LOGGER_H__
#define  __DYNWS_LOGGER_H__

using namespace std;

#include <string>

#define WL_DEBUG "DEBUG"
#define WL_INFO "INFO"
#define WL_ERROR "ERROR"
#define WL_FATAL "FATAL"

namespace dynws
{
	typedef string WL_LEVEL;

	class Logger 
	{

	public:
		void debug(string message);
		void debugBytes(string message);
		void info(string message);
		void error(string message);
		void fatal(string message);

	protected:
		void log(WL_LEVEL level, string message);
		void logBytes(WL_LEVEL level, string message);
		
	};

}	// namespace dynws

#endif