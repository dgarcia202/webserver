#include <iostream>
#include <csignal>
#include <stdlib.h>

#include "webserver.h"
#include "stringtools.h"
#include "webapp.h"

dynws::WebServer server;

void signalHandler(int signal)
{
	server.Stop();
	std::cout << "bye!" << std::endl;
	exit(signal);
}

int main()
{
	signal(SIGINT, signalHandler);

	HomeControllerFactory home_ctlr_factory;
	dynws::WebServer::router_.RegisterRoute("^\\/$", &home_ctlr_factory);

	QueryStringControllerFactory query_string_ctrl_factory;
	dynws::WebServer::router_.RegisterRoute("^\\/customers\\?id=(.*)$", &query_string_ctrl_factory);

	server.Start(8886);
}
