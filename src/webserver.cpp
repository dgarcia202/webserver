#include <iostream>
// #include <cstring>
#include <vector>
#include <sstream>
#include <iterator>
#include <process.h>

#include "socket.h"
#include "webserver.h"
#include "requestwrapper.h"
#include "logger.h"
#include "stringtools.h"

namespace dynws 
{
	RequestHandler WebServer::request_handler_ = 0; 
	Logger WebServer::l_ = Logger();

	unsigned WebServer::Request(void *pScket)
	{
		RequestWrapper req_wrapper;
		req_wrapper.Process(*(reinterpret_cast<Socket*>(pScket)), request_handler_);
		return 0;
	}

	void WebServer::Shutdown()
	{
		l_.info(STR("Shutting down..."));
		running_ = false;

		if(socket_server_)
		{
			delete socket_server_;
		}
	}

	void WebServer::Start(unsigned int port, RequestHandler handler_func)
	{
		request_handler_ = handler_func;
		socket_server_ = new SocketServer(port, 5);

		l_.info(STR("listening on port " << port << "..."));
		running_ = true;
		
		while(running_)
		{
			Socket *pScket = socket_server_->Accept();

			if (pScket == NULL)
			{
				continue;
			}

			unsigned threadId;
			_beginthreadex(0, 0, Request, (void *)pScket, 0, &threadId);
		}
	}

	WebServer::WebServer()
	{
		running_ = false;
	}

	WebServer::~WebServer()
	{
		l_.info(STR("Shutting down..."));
		if (socket_server_)
		{
			delete socket_server_;
		}
	}

}	// namespace dynws