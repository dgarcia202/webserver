#ifndef __DYNWS_CONTROLLER_H__
#define  __DYNWS_CONTROLLER_H__

#include <string>
#include <map>

#include "json/json.hpp"

namespace dynws
{
  struct HttpRequest
  {
    std::string method;
    std::string uri;
    std::string http_version;
    std::string host;
    std::string path;
    std::string query_string;
    std::map<std::string, std::string> headers;
    std::multimap<std::string, std::string> query_params;
    nlohmann::json body;
  };

  struct HttpResponse
  {
    std::string status;
    std::map<std::string, std::string> headers;
    nlohmann::json body;
  };

  class Controller
  {
  public:
    virtual ~Controller() { }

    virtual void Get(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = R"({ "message" : "method not allowed" })"_json;
    }

    virtual void Post(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = R"({ "message" : "method not allowed" })"_json;
    }

    virtual void Put(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = R"({ "message" : "method not allowed" })"_json;
    }

    virtual void Patch(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = R"({ "message" : "method not allowed" })"_json;
    }

    virtual void Delete(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = R"({ "message" : "method not allowed" })"_json;
    }

    virtual void Copy(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = R"({ "message" : "method not allowed" })"_json;
    }
  };

  class ControllerFactory
  {
  public:
    virtual ~ControllerFactory() { }

    virtual Controller *CreateIntance() = 0;
  };
} // namespace dynws

#endif
