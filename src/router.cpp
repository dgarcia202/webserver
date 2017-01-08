#include <string>
#include <map>
#include <regex>

#include "router.h"
#include "controller.h"
#include "logger.h"

namespace dynws
{
  Logger Router::l_;

  void Router::RegisterRoute(std::string pattern, ControllerFactory *ctrl_fatory_ptr)
  {
    route_table_.insert(std::pair<std::string, ControllerFactory *>(pattern, ctrl_fatory_ptr));
  }

  Controller *Router::ResolveController(std::string uri)
  {
    l_.debug("Router resolving URI " + uri);

    for (auto it = route_table_.cbegin(); it != route_table_.cend(); ++it)
    {
      l_.debug("Considering route " + it->first);
      std::regex expr(it->first);
      std::smatch match;

      std::regex_match(uri, match, expr);
      if (!match.empty())
      {
        l_.debug("Matched with route " + it->first);
        ControllerFactory *factory = route_table_[it->first];
        return factory->CreateIntance();
      }
    }
    return nullptr;
  }

  void Router::RouteRequest(HttpRequest &request, HttpResponse &response)
  {
    if (request.method == "GET" && !request.body.empty()) {
      response.status = "400 Bad Request";
      response.body = R"({ "message" : "GET requests are not allowed to have a body" })"_json;
      return;
    }

    Controller *ctrl = ResolveController(request.uri);
		if (ctrl)
		{
			l_.debug("valid controller found. execution action " + request.method);
			if(request.method == "GET")
			{
				ctrl->Get(request, response);
			}
			else if (request.method == "POST")
			{
				ctrl->Post(request, response);
			}
			else if (request.method == "PUT")
			{
				ctrl->Put(request, response);
			}
			else if (request.method == "PATCH")
			{
				ctrl->Patch(request, response);
			}
			else if (request.method == "DELETE")
			{
				ctrl->Delete(request, response);
			}
			else if (request.method == "COPY")
			{
				ctrl->Copy(request, response);
			}
      else if (request.method == "HEAD")
      {
        ctrl->Head(request, response);
      }
			else
			{
				response.status = "400 Bad Request";
				response.body = R"({ "message" : "illegal HTTP request method" })"_json;
			}
			delete ctrl;
		}
		else
		{
				response.status = "404 Not Found";
				response.body = R"({ "message" : "resource not found" })"_json;
		}
  }
} // namespace dynws
