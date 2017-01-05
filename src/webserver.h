
#ifndef __DYNWS_WEBSERVER_H__
#define __DYNWS_WEBSERVER_H__

#include <string>
#include <map>

#include "logger.h"
#include "socket.h"
#include "stringtools.h"

namespace dynws
{
	struct HttpRequest
	{
		std::string method;
		std::string uri;
		std::string http_version;
		std::string host;
		std::string path;
		std::string query_string;
		std::map<std::string, std::string> headers;

		std::string body;
	};

	struct HttpResponse
	{
		std::string status;
		std::map<std::string, std::string> headers;
		std::string body;
	};

	typedef void (* RequestHandler)(HttpRequest&, HttpResponse&);
	
	class WebServer
	{
		private:

			static RequestHandler request_handler_;
			static Logger l_;
			static unsigned __stdcall Request(void *);

			SocketServer *socket_server_;
			bool running_;
					
		public:

			WebServer(unsigned int , RequestHandler);
			WebServer();
			~WebServer();

			void Start(unsigned int, RequestHandler);
			void Shutdown();
	};

}	// namespace dynws

#endif