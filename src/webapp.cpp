#include "webapp.h"

dynws::Controller *HomeControllerFactory::CreateIntance()
{
	return new HomeController();
}

void HomeController::Get(dynws::HttpRequest &request, dynws::HttpResponse &response)
{
	response.status = "200 OK";
	response.body["requestData"]["method"] = request.method;
	response.body["requestData"]["uri"] = request.uri;
	response.body["requestData"]["httpVersion"] = request.http_version;

	response.body["requestData"]["host"] = request.host;
	response.body["requestData"]["path"] = request.path;
	response.body["requestData"]["query_string"] = request.query_string;

	int count = 0;
	for (auto it_headers = request.headers.begin(); it_headers != request.headers.end(); ++it_headers)
	{
		response.body["requestData"]["headers"][count]["key"] = it_headers->first;
		response.body["requestData"]["headers"][count]["value"] = it_headers->second;
		count++;
	}
}

dynws::Controller *QueryStringControllerFactory::CreateIntance()
{
	return new QueryStringController();
}

void QueryStringController::Get(dynws::HttpRequest &request, dynws::HttpResponse &response)
{
	response.status = "200 OK";
	for (auto it_params = request.query_params.begin(); it_params != request.query_params.end(); ++it_params)
	{
		response.body["queryParams"][it_params->first] = it_params->second;
	}

}

dynws::Controller *CustomerControllerFactory::CreateIntance()
{
	return new CustomerController();
}

void CustomerController::Post(dynws::HttpRequest &request, dynws::HttpResponse &response)
{
	if (!request.body.empty())
	{
		response.status = "200 OK";
		response.body["message"] = "Customer created with name " + request.body["name"].get<std::string>();
	}
	else
	{
		response.status = "400 Bad Request";
		response.body["message"] = "No customer data provided";
	}
}
