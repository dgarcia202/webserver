#include "webapp.h"

void HomeController::Action(dynws::HttpRequest &request, dynws::HttpResponse &response)
{
	response.status = "200 OK";
	response.body = "<h1>I'm the Home Controller</h1>";
}
