#include <iostream>
#include <csignal>
#include <stdlib.h>

#include "DynWS.h"

using namespace std;

DynWS server;

void signalHandler(int signal)
{
	server.Shutdown();	

	cout << "bye!" << NEWLINE;
	exit(signal);
}

void requestHandler(DynWS::HttpRequest *request, DynWS::HttpResponse *response)
{
	response->Status = "200 OK";
	response->Body = "<h1>Hello World!!</h1>";
}

int main() 
{
	signal(SIGINT, signalHandler);

	server.Start(8886, &requestHandler);
}