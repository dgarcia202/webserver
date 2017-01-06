#include <iostream>
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
	Logger WebServer::l_;
	Router WebServer::router_;

	unsigned WebServer::Request(void *pScket)
	{
		RequestWrapper req_wrapper;
		req_wrapper.Process(*(reinterpret_cast<Socket*>(pScket)), router_);
		return 0;
	}

	void WebServer::Stop()
	{
		l_.info(STR("stopping server..."));
		running_ = false;
	}

	void WebServer::Start(unsigned int port)
	{
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
		if (socket_server_)
		{
			delete socket_server_;
		}
	}

}	// namespace dynws
