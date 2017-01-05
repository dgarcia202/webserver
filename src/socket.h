
#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <winsock2.h>

#include "logger.h"

using namespace std;

namespace dynws
{
	class Socket
	{
		public:
			Socket(SOCKET s);
			~Socket();
			string ReceiveLine();
			string ReceiveBytes();
			void SendLine(string);
			void SendBytes(const string&);
			void Close();

		private:
			static Logger l;
			SOCKET s;
		};

		class SocketServer 
		{
		public:
			SocketServer(int, int);
			~SocketServer();
			Socket *Accept();
			void Close();

		private:
			static Logger l;
			SOCKET s;
	};

}	// namespace dynws

#endif