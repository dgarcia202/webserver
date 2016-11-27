
#ifndef __DYNWS_H__
#define __DYNWS_H__

#include <string>
#include <sstream>

#include "logger.h"

using namespace std;

#define NEWLINE "\n"

#define STR(x) static_cast<ostringstream&>(ostringstream() << dec << x).str()

class DynWS
{
	public:
		struct HttpRequest
		{
			string Method;
		};

		typedef void (* RequestHandler)(HttpRequest*);
		DynWS(unsigned int port, RequestHandler);

	private:
		static RequestHandler requestHandler;
		static Logger l;
		static unsigned __stdcall Request(void *pScket);
};

#endif