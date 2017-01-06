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
    std::map<std::string, Controller*> route_table_;

  public:
    void RegisterRoute(std::string, Controller*);
    Controller *ResolveController(std::string);
  };
} // namespace dynws

#endif
