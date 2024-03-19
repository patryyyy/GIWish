#ifndef GIWISH_CH_WISH_H_
#define GIWISH_CH_WISH_H_

#include <vector>
#include <random>
#include <ctime>

namespace GIWish {
typedef int Level;

const Level FIVE_STAR = 0;
const Level FOUR_STAR = 1;
const Level THREE_STAR = 2;

const int UP = 0;
const int STANDARD = 1;

const int WEAPONS = 0;
const int CHARACTERS = 1;

const int WISH_OK = 0;
const int WISH_ILLEGAL_PROBABILITY = 0x01;

struct CharactersWishInfo {
  std::time_t time;
  std::string format_time;
  int times = 0;
  std::string name;
  Level level;
};

struct CharactersWish {
 public:
  CharactersWish(double initial_five_star_probability,
                 double initial_four_star_probability,
                 double initial_three_star_probability,
                 int times_of_last_five_star,
                 int times_of_last_four_star,
                 bool is_get_standard_five_star,
                 bool is_get_standard_four_star);
  int wish(CharactersWishInfo &result);

 private:
  double initial_five_star_probability;
  double initial_four_star_probability;
  double initial_three_star_probability;
  double current_five_star_probability;
  double current_four_star_probability;
  double current_three_star_probability;
  int times_of_last_five_star;
  int times_of_last_four_star;
  bool is_get_standard_five_star;
  bool is_get_standard_four_star;
};


}

#endif //GIWISH_CH_WISH_H_
