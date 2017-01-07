#include <iostream>
#include <csignal>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <regex>

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

bool IsPortNumber(std::string literal)
{
	std::regex expr("^\\d{1,5}$");
	return std::regex_match(literal, expr);
}

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		std::cerr << "error: incorrect number of arguments";
		exit(1);
	}

	int port = 8886;
	if (argc == 2)
	{
		if (!IsPortNumber(std::string(argv[1])))
		{
			std::cerr << "error: incorrect argument format";
			exit(1);
		}
		port = atoi(argv[1]);
	}

	signal(SIGINT, signalHandler);

	HomeControllerFactory home_ctlr_factory;
	dynws::WebServer::router_.RegisterRoute("^\\/$", &home_ctlr_factory);

	QueryStringControllerFactory query_string_ctrl_factory;
	dynws::WebServer::router_.RegisterRoute("^\\/customers\\?id=(.*)$", &query_string_ctrl_factory);

	server.Start(port);
}
