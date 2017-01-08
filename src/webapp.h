#ifndef __WEBAPP_H__
#define __WEBAPP_H__

#include "controller.h"
#include "webserver.h"

class HomeController : public dynws::Controller
{
public:
	void Get(dynws::HttpRequest&, dynws::HttpResponse&);
	void Post(dynws::HttpRequest&, dynws::HttpResponse&);
};

class HomeControllerFactory : public dynws::ControllerFactory
{
public:
	dynws::Controller *CreateIntance();
};

class QueryStringController : public dynws::Controller
{
public:
	void Get(dynws::HttpRequest&, dynws::HttpResponse&);
};

class QueryStringControllerFactory : public dynws::ControllerFactory
{
public:
	dynws::Controller *CreateIntance();
};

#endif
