#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <process.h>

#include "socket.h"
#include "dynws.h"
#include "logger.h"

DynWS::RequestHandler DynWS::requestHandler = 0; 
Logger DynWS::l = Logger();

std::vector<std::string> str_split(std::string s, char delim);

unsigned DynWS::Request(void *pScket)
{
	Socket s = *(reinterpret_cast<Socket*>(pScket));

	HttpRequest request;
	HttpResponse response;

	while (true)
	{
		string line = s.ReceiveLine();

		if (line.empty() || line.find_first_of("\x0a\x0d") == 0)
		{
			break;
		}

		l.debugBytes(STR(line));
	}

	request.Method = "GET";
	requestHandler(&request, &response);

	s.SendBytes("HTTP/1.1 ");
	s.SendLine(response.Status);
	s.SendLine("");
	s.SendLine(response.Body);
	s.Close();

	return 0;
}

void DynWS::Shutdown()
{
	l.info(STR("Shutting down..."));
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
	
	while(true)
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
}

DynWS::~DynWS()
{
	l.info(STR("Shutting down..."));
	if (socketServer)
	{
		delete socketServer;
	}
}

std::vector<std::string> str_split(std::string s, char delim)
{
	using namespace std;
	
	vector<string> tokens;
	istringstream iss(s);
	
	copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(tokens));
	
	return tokens;
}