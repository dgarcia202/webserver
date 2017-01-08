#ifndef __DYNWS_ROUTER_H__
#define __DYNWS_ROUTER_H__

#include <string>
#include <map>

#include "logger.h"
#include "controller.h"

namespace dynws
{
  class Router
  {
  private:
    static Logger l_;
    std::map<std::string, ControllerFactory*> route_table_;
    
    Controller *ResolveController(std::string);

  public:
    void RegisterRoute(std::string, ControllerFactory*);
    void RouteRequest(HttpRequest&, HttpResponse&);
  };
} // namespace dynws

#endif
