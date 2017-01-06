#ifndef __WEBAPP_H__
#define __WEBAPP_H__

#include "controller.h"
#include "webserver.h"

class HomeController : public dynws::Controller
{
public:
	void Action(dynws::HttpRequest&, dynws::HttpResponse&);
};

#endif
