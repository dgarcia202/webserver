#include "webapp.h"

dynws::Controller *HomeControllerFactory::CreateIntance()
{
	return new HomeController();
}

void HomeController::Action(dynws::HttpRequest &request, dynws::HttpResponse &response)
{
	response.status = "200 OK";
	response.body = "<h1>Hello World!!</h1>"
						"<ul>"
						"<li><b>Method</b>: " + request.method + "</li>"
						"<li><b>URI</b>: " + request.uri + "</li>"
						"<li><b>HTTP Version</b>: " + request.http_version + "</li>"
						"<li><b>Host</b>: " + request.host + "</li>"
						"<li><b>Path</b>: " + request.path + "</li>"
						"<li><b>Query string</b>: " + request.query_string + "</li>"
						"</ul>";

	response.body += "<h2>Headers</h2>"
						"<ul>";

	map<string, string>::const_iterator it;
	for (it = request.headers.begin(); it != request.headers.end(); ++it)
	{
		response.body += "<li>" + it->first + ": " + it->second + "</li>";
	}

	response.body += "</ul>";

	if (!response.body.empty())
	{
		response.body += "<h2>Request content</h2>";
		response.body += "<p>" + request.body + "</p>";
	}
}
