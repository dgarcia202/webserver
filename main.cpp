#include <iostream>
#include <csignal>
#include <stdlib.h>

#include "DynWS.h"
#include "stringtools.h"

using namespace std;

DynWS server;

void signalHandler(int signal)
{
	server.Shutdown();	

	cout << "bye!" << endl;
	exit(signal);
}

void requestHandler(DynWS::HttpRequest *request, DynWS::HttpResponse *response)
{
	response->status = "200 OK";
	response->body = "<h1>Hello World!!</h1>"
						"<ul>"
						"<li><b>Method</b>: " + request->method + "</li>"
						"<li><b>URI</b>: " + request->uri + "</li>"
						"<li><b>HTTP Version</b>: " + request->http_version + "</li>"
						"<li><b>Host</b>: " + request->host + "</li>"
						"</ul>";

	response->body += "<h2>Headers</h2>"
						"<ul>";

	map<string, string>::iterator it;
	for (it = request->headers.begin(); it != request->headers.end(); ++it)
	{
		response->body += "<li>" + it->first + ": " + it->second + "</li>";
	}

	response->body += "</ul>";
}

int main() 
{
	signal(SIGINT, signalHandler);

	server.Start(8886, &requestHandler);
}