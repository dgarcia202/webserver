#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <process.h>

#include "socket.h"
#include "dynws.h"
#include "logger.h"
#include "stringtools.h"

DynWS::RequestHandler DynWS::request_handler_ = 0; 
Logger DynWS::l_ = Logger();

unsigned DynWS::Request(void *pScket)
{
	using namespace strtools;

	Socket s = *(reinterpret_cast<Socket*>(pScket));

	HttpRequest request;
	HttpResponse response;

	int lines_count = 0;
	bool reading_body = false;
	while (true)
	{
		std::string line = reading_body ? s.ReceiveBytes() : s.ReceiveLine();
		lines_count++;

		if (reading_body && line.empty())
		{
			break;
		}

		if (line.find_first_of("\x0a\x0d") == 0)
		{
			reading_body = true;
			continue;
		}

		if (lines_count == 1)
		{
			std::vector<std::string> pieces = strsplit(line, ' ');
			request.method = pieces[0];
			request.uri = pieces[1];
			request.http_version = pieces[2];
			
			int question_mark_pos = request.uri.find("?");
			request.path = request.uri.substr(0, question_mark_pos);
			request.query_string = request.uri.substr(question_mark_pos + 1);
		}
		else if (!reading_body)
		{
			int separator_pos = line.find(":");
			std::string key = trim_cp(line.substr(0, separator_pos));
			std::string value = trim_cp(line.substr(separator_pos + 1));
			if (toupper_cp(key) == "HOST")
			{
				request.host = value;
			}
			else
			{
				request.headers.insert(std::pair<std::string, std::string>(key, value));
			}
		}
		else
		{
			request.body += line;
		}
		
		l_.debugBytes(STR(line));
	}

	request_handler_(&request, &response);

	s.SendBytes("HTTP/1.1 ");
	s.SendLine(response.status);
	s.SendLine("");
	s.SendLine(response.body);
	s.Close();

	return 0;
}

void DynWS::Shutdown()
{
	l_.info(STR("Shutting down..."));
	running_ = false;

	if(socket_server_)
	{
		delete socket_server_;
	}
}

void DynWS::Start(unsigned int port, RequestHandler handler_func)
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

DynWS::DynWS()
{
	running_ = false;
}

DynWS::~DynWS()
{
	l_.info(STR("Shutting down..."));
	if (socket_server_)
	{
		delete socket_server_;
	}
}