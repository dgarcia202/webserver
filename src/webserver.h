
#ifndef __DYNWS_WEBSERVER_H__
#define __DYNWS_WEBSERVER_H__

#include <string>
#include <map>

#include "logger.h"
#include "socket.h"
#include "controller.h"
#include "router.h"
#include "stringtools.h"

namespace dynws
{
	typedef void (Controller::*RequestHandler)(HttpRequest&, HttpResponse&);

	class WebServer
	{
	public:

		WebServer();
		~WebServer();

		void Start(unsigned int);
		void Stop();

		static Router router_;

	private:
		static Logger l_;
		static unsigned __stdcall Request(void *);

		bool running_;
		SocketServer *socket_server_;
	};

}	// namespace dynws

#endif
