#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <process.h>

#include "socket.h"
#include "dynws.h"
#include "logger.h"
#include "stringtools.h"

DynWS::RequestHandler DynWS::requestHandler = 0; 
Logger DynWS::l = Logger();

std::vector<std::string> StringSplit(std::string s, char delim);

unsigned DynWS::Request(void *pScket)
{
	using namespace strtools;

	Socket s = *(reinterpret_cast<Socket*>(pScket));

	HttpRequest request;
	HttpResponse response;

	int lines_count = 0;
	while (true)
	{
		std::string line = s.ReceiveLine();
		lines_count++;
		
		if (line.empty() || line.find_first_of("\x0a\x0d") == 0)
		{
			break;
		}

		if (lines_count == 1)
		{
			std::vector<std::string> pieces = StringSplit(line, ' ');
			request.method = pieces[0];
			request.uri = pieces[1];
			request.http_version = pieces[2];
		}
		else
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
		
		l.debugBytes(STR(line));
	}

	requestHandler(&request, &response);

	s.SendBytes("HTTP/1.1 ");
	s.SendLine(response.status);
	s.SendLine("");
	s.SendLine(response.body);
	s.Close();

	return 0;
}

void DynWS::Shutdown()
{
	l.info(STR("Shutting down..."));
	running_ = false;

	if (socketServer)
	{
		delete socketServer;
	}
}

void DynWS::Start(unsigned int port, RequestHandler handlerFunc)
{
	requestHandler = handlerFunc;
	socketServer = new SocketServer(port, 5);

	l.info(STR("listening on port " << port << "..."));
	running_ = true;
	
	while(running_)
	{
		Socket *pScket = socketServer->Accept();

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
	l.info(STR("Shutting down..."));
	if (socketServer)
	{
		delete socketServer;
	}
}

std::vector<std::string> StringSplit(std::string s, char delim)
{
	using namespace std;
	
	vector<string> tokens;
	istringstream iss(s);
	
	copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(tokens));
	
	return tokens;
}