#include <string>
#include <map>

#include "router.h"
#include "controller.h"
#include "logger.h"

namespace dynws
{
  Logger Router::l_;

  void Router::RegisterRoute(std::string pattern, Controller &handler)
  {
    route_table_.insert(std::pair<std::string, Controller&>(pattern, handler));
  }

  Controller *ResolveController(std::string)
  {
    // TODO: not implemented
  }
} // namespace dynws
