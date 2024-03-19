#include <GIWish/wish.h>
#include <GIWish/time_util.h>
#include <iostream>
#include <random>

namespace GIWish {
static std::mt19937 gen(std::random_device{}());
static std::discrete_distribution<int> fifty_and_fifty({50, 50});
static std::discrete_distribution<int> random_four_and_five_star({0.6, 99.4});
static std::uniform_int_distribution<int> random_five_star_characters(0, (int) five_star_characters.size() - 1);
static std::uniform_int_distribution<int> random_four_star_weapons(0, (int) four_star_weapons.size() - 1);
static std::uniform_int_distribution<int> random_four_star_characters(0, (int) four_star_characters.size() - 1);
static std::uniform_int_distribution<int> random_four_star_up_characters(0, (int) four_star_up_characters.size() - 1);
static std::uniform_int_distribution<int> random_three_star_weapons(0, (int) three_star_weapons.size() - 1);

CharactersWish::CharactersWish(double initial_five_star_probability,
                               double initial_four_star_probability,
                               double initial_three_star_probability,
                               int times_of_last_five_star,
                               int times_of_last_four_star,
                               bool is_get_standard_five_star,
                               bool is_get_standard_four_star) {
  this->initial_five_star_probability = this->current_five_star_probability = initial_five_star_probability;
  this->initial_four_star_probability = this->current_four_star_probability = initial_four_star_probability;
  this->initial_three_star_probability = this->current_three_star_probability = initial_three_star_probability;
  this->times_of_last_five_star = times_of_last_five_star;
  this->times_of_last_four_star = times_of_last_four_star;
  this->is_get_standard_five_star = is_get_standard_five_star;
  this->is_get_standard_four_star = is_get_standard_four_star;
}

int CharactersWish::wish(CharactersWishInfo &result) {
  if (initial_five_star_probability < 0 || initial_four_star_probability < 0 || initial_three_star_probability < 0) {
    return WISH_ILLEGAL_PROBABILITY;
  }

  /* Record time */
  auto time = std::chrono::system_clock::now();
  result.time = get_time_t(time);
  result.format_time = get_format_time(time);

  /* After 74th wishes(including 74th), 5-star probability increase */
  if (times_of_last_five_star >= 73) {
    current_five_star_probability += 6;
    current_four_star_probability -= 0.30784708;
    current_three_star_probability -= 5.69215292;
    if (current_three_star_probability <= 0 || current_four_star_probability <= 0) {
      current_three_star_probability = 0;
      current_four_star_probability = 0;
    }
  }

  /* Initialize variables */
  std::discrete_distribution<int> base_probabilities
      ({current_five_star_probability, current_four_star_probability, current_three_star_probability});


  /* Determine number of item stars */
  result.level = base_probabilities(gen);

  if (times_of_last_five_star == 89) {
    result.level = FIVE_STAR;
  } else if (times_of_last_four_star == 9) {
    result.level = random_four_and_five_star(gen);
  }

  /* Reset state */
  switch (result.level) {
    case FIVE_STAR:
      times_of_last_five_star = 0;
      current_five_star_probability = initial_five_star_probability;
      current_four_star_probability = initial_four_star_probability;
      current_three_star_probability = initial_three_star_probability;
      break;
    case FOUR_STAR:
      times_of_last_four_star = 0;
      times_of_last_five_star++;
      break;
    case THREE_STAR:
      times_of_last_four_star++;
      times_of_last_five_star++;
      break;
  }

  /* Determine the final item */
  switch (result.level) {
    case FIVE_STAR:
      if (!is_get_standard_five_star) {
        int standard_or_up = fifty_and_fifty(gen);

        if (standard_or_up == UP) {
          is_get_standard_five_star = false;
          result.name = five_star_up_characters;
        } else if (standard_or_up == STANDARD) {
          is_get_standard_five_star = true;
          result.name = five_star_characters[random_five_star_characters(gen)];
        }
      } else {
        is_get_standard_five_star = false;
        result.name = five_star_up_characters;
      }
      break;
    case FOUR_STAR:
      /* 1.Don't have 4-star item */
      if (!is_get_standard_four_star) {
        int weapons_or_characters = fifty_and_fifty(gen);

        /* Weapons */
        if (weapons_or_characters == WEAPONS) {
          is_get_standard_four_star = true;
          result.name = four_star_weapons[random_four_star_weapons(gen)];
        }

          /* Characters */
        else if (weapons_or_characters == CHARACTERS) {
          int standard_or_up = fifty_and_fifty(gen);

          if (standard_or_up == UP) {
            is_get_standard_four_star = false;
            result.name = four_star_up_characters[random_four_star_up_characters(gen)];
          } else if (standard_or_up == STANDARD) {
            is_get_standard_four_star = true;
            result.name = four_star_characters[random_four_star_characters(gen)];
          }
        }
      }

        /* 2.Already have a standard 4-star item */
      else {
        is_get_standard_four_star = false;
        result.name = four_star_up_characters[random_four_star_up_characters(gen)];
      }
      break;
    case THREE_STAR:
      result.name = three_star_weapons[random_three_star_weapons(gen)];
      break;
  }

  result.times++;
  return WISH_OK;
}
}

