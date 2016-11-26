
#include "socketCtrl.h"
#include "webserver.h"

webserver::webserver(unsigned int port, void (*handlerFunc)(httpRequest*))
{
	requestHandler = handlerFunc;
	socketCtrl s(port, 5);

	httpRequest r;
	r.method = "X4344X";
	requestHandler(&r);
}