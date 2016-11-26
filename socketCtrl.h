
#ifndef __SOCKETCTRL_H__
#define __SOCKETCTRL_H__

#include <winsock2.h>

class socketCtrl 
{
	public:
		socketCtrl(int port, int connections);

		SOCKET s;
};

#endif