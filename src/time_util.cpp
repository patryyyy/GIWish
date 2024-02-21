#include <iomanip>
#include <sstream>
#include <GIWish/time_util.h>

namespace GIWish {
std::time_t get_time_t(std::chrono::time_point<std::chrono::system_clock> t) {
  return std::chrono::system_clock::to_time_t(t);
}

std::string get_format_time(std::chrono::time_point<std::chrono::system_clock> t) {
  std::ostringstream oss;
  std::time_t current_time = get_time_t(t);
  oss << std::put_time(std::localtime(&current_time), "%Y-%m-%d %H:%M:%S");
  return oss.str();
}
}
