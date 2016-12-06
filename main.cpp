#include <iostream>
#include <csignal>
#include <stdlib.h>

#include "DynWS.h"

using namespace std;

DynWS *dynWs;

void signalHandler(int signal)
{
//	delete dynWs;
	dynWs->Shutdown();
	delete dynWs;
	
	cout << "bye!";
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

	dynWs = new DynWS(8886, &requestHandler);
}