#include <iostream>
#include <winsock2.h>

#include "socket.h"
#include "dynws.h"
#include "logger.h"

using namespace std;

Logger SocketServer::l = Logger();

Socket::Socket(SOCKET s)
{
	this->s = s;
}

void Socket::Close()
{
	closesocket(s);
}

string Socket::ReceiveLine()
{
	string ret;
	while(true)
	{
		char r;
		switch(recv(s, &r, 1, 0))
		{
			case 0:
				return "";

			case -1:
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					continue;
				}
				else
				{
					return "";
				}
		}

		ret += r;
		if (r == '\n')
		{
			return ret;
		}
	}
}

void Socket::SendLine(string line)
{
	line += NEWLINE;
	send(s, line.c_str(), line.length(), 0);
}

void Socket::SendBytes(const string& bytes)
{
	send(s, bytes.c_str(), bytes.length(), 0);
}

SocketServer::SocketServer(int port, int connections)
{
	WORD versionRequested;
	WSADATA wsaData;

	versionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(versionRequested, &wsaData);

	if (err != 0)
	{
		l.Fatal(STR("WSAStartup failed (error:" << err << ")"));
		throw "SA_STARTUP_FAILED";
	}
	else
	{
		l.Info(STR("version: " << wsaData.wVersion));
		l.Info(STR("high version: " << wsaData.szDescription));
		l.Info(STR("description: " << wsaData.wHighVersion));
		l.Info(STR("system status: " << wsaData.szSystemStatus));
		l.Info(STR("max sockets: " << wsaData.iMaxSockets));
		l.Info(STR("max UDG dg:" << wsaData.iMaxUdpDg));
	}

	sockaddr_in address;
	memset(&address, 0, sizeof(address));

	address.sin_family = PF_INET;
	address.sin_port = htons(port);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		l.Fatal(STR("Open TCP socket failed! (error:" << WSAGetLastError() << ")"));
		throw "INVALID_SOCKET";
	}

	// make non-blocking
    u_long arg = 1;
    err = ioctlsocket(s, FIONBIO, &arg);
    if (err == SOCKET_ERROR)
    {
    	l.Fatal(STR("Change to non-blocking failed (error:" << WSAGetLastError()  << ")"));
    	throw "SOCKET_ERROR";
    }

    // binding
    if (bind(s, (sockaddr *)&address, sizeof(sockaddr_in)) == SOCKET_ERROR) 
    {
    	closesocket(s);
    	l.Fatal(STR("Failed socket bind (error:" << WSAGetLastError()  << ")"));
    	throw "SOCKET_ERROR";
	}

	listen(s, connections);
}

Socket *SocketServer::Accept()
{
	SOCKET newSock = accept(s, 0, 0);
	if (newSock == INVALID_SOCKET)
	{
		int err = WSAGetLastError();
		if (err == WSAEWOULDBLOCK)
		{
			return NULL;
		}
		else
		{
			l.Fatal(STR("Open accepted TCP socket failed! (error:" << err << ")"));
			throw "INVALID_SOCKET";			
		}
	}

	return new Socket(newSock);
}