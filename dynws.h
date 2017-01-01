
#ifndef __DYNWS_H__
#define __DYNWS_H__

#include <string>
#include <sstream>
#include <map>

#include "logger.h"
#include "socket.h"

#define NEWLINE "\n"

#define STR(x) static_cast<ostringstream&>(ostringstream() << dec << x).str()

class DynWS
{
	public:
		struct HttpRequest
		{
			std::string Method;
			std::map<std::string, std::string> headers;
		};

		struct HttpResponse
		{
			std::string Status;
			std::map<std::string, std::string> headers;
			std::string Body;
		};

		typedef void (* RequestHandler)(HttpRequest*, HttpResponse*);
		DynWS(unsigned int , RequestHandler);
		DynWS();
		~DynWS();

		void Start(unsigned int, RequestHandler);
		void Shutdown();

	private:
		static RequestHandler requestHandler;
		static Logger l;
		static unsigned __stdcall Request(void *);

		SocketServer *socketServer;
};

#endif