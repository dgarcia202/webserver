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
/*
	HttpRequest r;
	r.Method = "X4344X";

	requestHandler(&r);
	*/

	while (true)
	{
		string line = s.ReceiveLine();

		if (line == "")
		{
			break;
		}

		l.Con(">>>" + line);
	}

	l.Con("+++ answering a fake OK");

	s.SendBytes("HTTP/1.1 ");
	s.SendLine("200 OK");
	s.SendLine("");
	s.Close();

	return 0;
}

DynWS::DynWS(unsigned int port, RequestHandler handlerFunc)
{
	requestHandler = handlerFunc;
	SocketServer sockSvr(port, 5);

	l.Con(STR("listening on port " << port));
	
	while(true)
	{
		Socket *pScket = sockSvr.Accept();

		if (pScket == NULL)
		{
			continue;
		}

		unsigned threadId;
		_beginthreadex(0, 0, Request, (void *)pScket, 0, &threadId);
	}
}

