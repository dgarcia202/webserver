#include <iostream>
#include <winsock2.h>

#include "socketCtrl.h"
#include "webserver.h"
#include "logger.h"

using namespace std;

logger l = logger();

socketCtrl::socketCtrl(int port, int connections)
{
	WORD versionRequested;
	WSADATA wsaData;

	versionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(versionRequested, &wsaData);

	if (err != 0)
	{
		l.fatal(STR("WSAStartup failed (error:" << err << ")"));
		throw "SA_STARTUP_FAILED";
	}
	else
	{
		l.info(STR("version: " << wsaData.wVersion));
		l.info(STR("high version: " << wsaData.szDescription));
		l.info(STR("description: " << wsaData.wHighVersion));
		l.info(STR("system status: " << wsaData.szSystemStatus));
		l.info(STR("max sockets: " << wsaData.iMaxSockets));
		l.info(STR("max UDG dg:" << wsaData.iMaxUdpDg));
	}

	sockaddr_in address;
	memset(&address, 0, sizeof(address));

	address.sin_family = PF_INET;
	address.sin_port = htons(port);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		l.fatal(STR("Open TCP socket failed! (error:" << WSAGetLastError() << ")"));
		throw "INVALID_SOCKET";
	}

	// make non-blocking
    u_long arg = 1;
    err = ioctlsocket(s, FIONBIO, &arg);
    if (err == SOCKET_ERROR)
    {
    	l.fatal(STR("Change to non-blocking failed (error:" << WSAGetLastError()  << ")"));
    	throw "SOCKET_ERROR";
    }

    // binding
    if (bind(s, (sockaddr *)&address, sizeof(sockaddr_in)) == SOCKET_ERROR) 
    {
    	closesocket(s);
    	l.fatal(STR("Failed socket bind (error:" << WSAGetLastError()  << ")"));
    	throw "SOCKET_ERROR";
	}

	listen(s, connections);
}

SOCKET socketCtrl::acceptNew()
{
	SOCKET newSock = accept(s, 0, 0);
	if (newSock == INVALID_SOCKET)
	{
		l.fatal(STR("Open accepted TCP socket failed! (error:" << WSAGetLastError() << ")"));
		throw "INVALID_SOCKET";
	}

	return newSock;
}