#include <iostream>
#include <csignal>
#include <stdlib.h>

#include "webserver.h"
#include "stringtools.h"
#include "webapp.h"

using namespace std;

dynws::WebServer server;

void signalHandler(int signal)
{
	server.Stop();

	cout << "bye!" << endl;
	exit(signal);
}

int main()
{
	signal(SIGINT, signalHandler);

	HomeControllerFactory home_ctlr_factory;
	dynws::WebServer::router_.RegisterRoute("/", &home_ctlr_factory);

	server.Start(8886);
}
