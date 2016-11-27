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

		if (line.empty())
		{
			break;
		}

    	unsigned int pos_cr_lf = line.find_first_of("\x0a\x0d");
    	if (pos_cr_lf == 0) break;

		l.Con(STR(">>>" << "(" << line.length() << ")" << line));
	}

	l.Con("+++ answering a fake OK");

	request.Method = "GET";
	requestHandler(&request, &response);

	s.SendBytes("HTTP/1.1 ");
	s.SendLine(response.Status);
	s.SendLine("");
	s.SendLine(response.Body);
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

