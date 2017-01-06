#include <string>
#include <map>

#include "router.h"
#include "controller.h"
#include "logger.h"

namespace dynws
{
  Logger Router::l_;

  void Router::RegisterRoute(std::string pattern, Controller *ctrl_ptr)
  {
    route_table_.insert(std::pair<std::string, Controller*>(pattern, ctrl_ptr));
  }

  Controller *Router::ResolveController(std::string pattern)
  {
    l_.debug("Router resolving URI " + pattern);
    return route_table_[pattern];
  }
} // namespace dynws
