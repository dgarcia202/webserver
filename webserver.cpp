#include <process.h>

#include "socketCtrl.h"
#include "webserver.h"

logger l = logger();

unsigned __stdcall webserver::requestProcessor(void *pScket)
{
	l.debug("processing request!!");
	httpRequest r;
	r.method = "X4344X";

	requestHandler(&r);
}

webserver::webserver(unsigned int port, void (*handlerFunc)(httpRequest*))
{
	requestHandler = handlerFunc;
	socketCtrl sctrl(port, 5);
	while(true)
	{
		SOCKET pScket = sctrl.acceptNew();

		unsigned threadId;
		_beginthreadex(0, 0, requestProcessor, (void *)pScket, 0, &threadId);
	}

	
}

