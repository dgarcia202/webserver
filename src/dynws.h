
#ifndef __DYNWS_H__
#define __DYNWS_H__

#include <string>
#include <map>

#include "logger.h"
#include "socket.h"
#include "stringtools.h"

class DynWS
{
	public:
		struct HttpRequest
		{
			std::string method;
			std::string uri;
			std::string http_version;
			std::string host;
			std::map<std::string, std::string> headers;

			std::string body;
		};

		struct HttpResponse
		{
			std::string status;
			std::map<std::string, std::string> headers;
			std::string body;
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
		bool running_;
};

#endif