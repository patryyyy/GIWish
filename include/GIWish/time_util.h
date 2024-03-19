#ifndef GIWISH_TIME_UTIL_H_
#define GIWISH_TIME_UTIL_H_

#include <chrono>
#include <ctime>

namespace GIWish {
std::time_t get_time_t(std::chrono::time_point<std::chrono::system_clock> t);
std::string get_format_time(std::chrono::time_point<std::chrono::system_clock> t);
}

#endif //GIWISH_TIME_UTIL_H_
