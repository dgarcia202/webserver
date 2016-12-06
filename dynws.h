
#ifndef __DYNWS_H__
#define __DYNWS_H__

#include <string>
#include <sstream>

#include "logger.h"
#include "socket.h"

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

		struct HttpResponse
		{
			string Status;
			string Body;
		};

		typedef void (* RequestHandler)(HttpRequest*, HttpResponse*);
		DynWS(unsigned int , RequestHandler);
		DynWS(const DynWS&);
		DynWS& operator=(DynWS&);
		~DynWS();

		void Shutdown();

	private:
		static RequestHandler requestHandler;
		static Logger l;
		static unsigned __stdcall Request(void *);

		SocketServer *socketServer;
};

#endif