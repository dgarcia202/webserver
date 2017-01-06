#include <string>
#include <map>

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

  Controller *Router::ResolveController(std::string pattern)
  {
    l_.debug("Router resolving URI " + pattern);
    ControllerFactory *factory = route_table_[pattern];
    return factory->CreateIntance();
  }
} // namespace dynws
