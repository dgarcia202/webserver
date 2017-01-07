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

	for (auto it_headers = request.headers.begin(); it_headers != request.headers.end(); ++it_headers)
	{
		response.body += "<li>" + it_headers->first + ": " + it_headers->second + "</li>";
	}

	response.body += "</ul>";

	if (!response.body.empty())
	{
		response.body += "<h2>Request content</h2>";
		response.body += "<p>" + request.body + "</p>";
	}
}

dynws::Controller *QueryStringControllerFactory::CreateIntance()
{
	return new QueryStringController();
}

void QueryStringController::Action(dynws::HttpRequest &request, dynws::HttpResponse &response)
{
	response.body += "<h2>Query Params</h2>"
						"<ul>";

	for (auto it_params = request.query_params.begin(); it_params != request.query_params.end(); ++it_params)
	{
		response.body += "<li>" + it_params->first + ": " + it_params->second + "</li>";
	}
	response.body += "</ul>";
}
