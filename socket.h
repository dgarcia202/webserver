
#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <winsock2.h>

#include "logger.h"

using namespace std;

class Socket
{
public:
	Socket(SOCKET s);
	//virtual ~Socket();
	string ReceiveLine();
	void SendLine(string);
	void SendBytes(const string&);
	void Close();

protected:
	
private:
	SOCKET s;
};

class SocketServer 
{
public:
	SocketServer(int, int);
	Socket *Accept();

private:
	static Logger l;
	SOCKET s;
};

#endif