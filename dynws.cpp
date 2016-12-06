#include <iostream>
#include <process.h>

#include "socket.h"
#include "dynws.h"
#include "logger.h"

DynWS::RequestHandler DynWS::requestHandler = 0; 
Logger DynWS::l = Logger();

using namespace std;

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

DynWS::DynWS(unsigned int port, RequestHandler handlerFunc)
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

DynWS::DynWS(const DynWS &o)
{
	requestHandler = o.requestHandler;
	l = o.l;
	socketServer = o.socketServer;
}

DynWS& DynWS::operator =(DynWS &o)
{
	requestHandler = o.requestHandler;
	l = o.l;
	socketServer = o.socketServer;	
	return *this;
}

DynWS::~DynWS()
{
	l.info(STR("Shutting down..."));
	if (socketServer)
	{
		delete socketServer;
	}
}
