#ifndef __DYNWS_CONTROLLER_H__
#define  __DYNWS_CONTROLLER_H__

#include <string>
#include <map>

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
    std::string body;
  };

  struct HttpResponse
  {
    std::string status;
    std::map<std::string, std::string> headers;
    std::string body;
  };

  class Controller
  {
  public:
    virtual ~Controller() { }

    virtual void Get(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = "{ \"message\" : \"method not allowed\" }";
    }

    virtual void Post(HttpRequest &request, HttpResponse &response)
    {
      /*response.status = "405 Method Not Allowed";
      response.body = "{ \"message\" : \"method not allowed\" }";*/
    }

    virtual void Put(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = "{ \"message\" : \"method not allowed\" }";
    }

    virtual void Patch(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = "{ \"message\" : \"method not allowed\" }";
    }

    virtual void Delete(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = "{ \"message\" : \"method not allowed\" }";
    }

    virtual void Copy(HttpRequest &request, HttpResponse &response)
    {
      response.status = "405 Method Not Allowed";
      response.body = "{ \"message\" : \"method not allowed\" }";
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
