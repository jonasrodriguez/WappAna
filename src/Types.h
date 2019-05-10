#pragma once

#include <ctime>
#include <string>

namespace wapp {

struct Chat {
  tm timeDate;
  std::string user;
  std::string text;
  int lineCount;
};

} // namespace wapp
