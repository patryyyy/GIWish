#include <vector>
#include <GIWish/wish.h>
#include <GIWish/time_util.h>

namespace GIWish {
WishManager::WishManager(double five_star_probability,
                         double four_star_probability,
                         double three_star_probability,
                         int times,
                         int times_of_last_five_star,
                         int times_of_last_four_star,
                         bool is_get_standard_five_star,
                         bool is_get_standard_four_star) {
  m_five_star_probability = five_star_probability;
  m_four_star_probability = four_star_probability;
  m_three_star_probability = three_star_probability;
  m_times = times;
  m_times_of_last_five_star = times_of_last_five_star;
  m_times_of_last_four_star = times_of_last_four_star;
  m_is_get_standard_five_star = is_get_standard_five_star;
  m_is_get_standard_four_star = is_get_standard_four_star;
}

int WishManager::wish(WishInfo &wish_info) {
  std::random_device rd;
  std::mt19937 gen(rd());

  /* Record time */
  auto time = std::chrono::system_clock::now();
  wish_info.time = get_time_t(time);
  wish_info.format_time = get_format_time(time);

  /* Initialize variables */
  Level level;

  std::vector<double> distribution{50, 50};
  std::discrete_distribution<int> p_distribution(distribution.begin(), distribution.end());

  std::vector<double> base_probabilities{m_five_star_probability, m_four_star_probability, m_three_star_probability};
  std::discrete_distribution<int> p_base_probabilities(base_probabilities.begin(), base_probabilities.end());

  std::vector<double> four_and_five_star_probabilities{0.6, 99.4};
  std::discrete_distribution<int> p_four_and_five_star_probabilities
      (four_and_five_star_probabilities.begin(), four_and_five_star_probabilities.end());

  std::uniform_int_distribution<int> p_five_star_characters(0, 6);

  std::uniform_int_distribution<int> p_four_star_weapons(0, 17);

  std::uniform_int_distribution<int> p_four_star_characters(0, 32);

  std::uniform_int_distribution<int> p_four_star_up_characters(0, 2);

  std::uniform_int_distribution<int> p_three_star_weapons(0, 12);

  /* Determine number of item stars */
  wish_info.level = level = static_cast<Level>(p_base_probabilities(gen));

  if (level == FIVE_STAR) {
    m_times_of_last_five_star = 0;
  } else if (level == FOUR_STAR) {
    m_times_of_last_four_star = 0;
  }

  /* Determine final number of item stars */
  if (m_times_of_last_five_star == 89) {
    wish_info.level = level = FIVE_STAR;
    m_times_of_last_five_star = 0;
  } else if (m_times_of_last_four_star == 9) {
    wish_info.level = level = static_cast<Level>(p_four_and_five_star_probabilities(gen));
    m_times_of_last_four_star = 0;
  }

  /* Determine the final item */
  switch (level) {
    case FIVE_STAR:
      if (!m_is_get_standard_five_star) {
        int standard_or_up = p_distribution(gen);

        if (standard_or_up == UP) {
          m_is_get_standard_five_star = false;
          wish_info.name = five_star_up_characters;
        } else if (standard_or_up == STANDARD) {
          m_is_get_standard_five_star = true;
          wish_info.name = five_star_characters[p_five_star_characters(gen)];
        }
      } else {
        m_is_get_standard_five_star = false;
        wish_info.name = five_star_up_characters;
      }

      m_times++;
      return WISH_OK;
    case FOUR_STAR:
      /* 1.Don't have Four-star item */
      if (!m_is_get_standard_four_star) {
        int weapons_or_characters = p_distribution(gen);

        /* Weapons */
        if (weapons_or_characters == WEAPONS) {
          m_is_get_standard_four_star = true;
          wish_info.name = four_star_weapons[p_four_star_weapons(gen)];
        }

          /* Characters */
        else if (weapons_or_characters == CHARACTERS) {
          int standard_or_up = p_distribution(gen);
          if (standard_or_up == UP) {
            m_is_get_standard_four_star = false;
            wish_info.name = four_star_up_characters[p_four_star_up_characters(gen)];
          } else {
            m_is_get_standard_four_star = true;
            wish_info.name = four_star_characters[p_four_star_characters(gen)];
          }
        }
      }

        /* 2.Already have a 4-star item */
      else {
        m_is_get_standard_four_star = false;
        wish_info.name = four_star_up_characters[p_four_star_up_characters(gen)];
      }

      m_times++;
      m_times_of_last_five_star++;
      return WISH_OK;
    case THREE_STAR:
      wish_info.name = three_star_weapons[p_three_star_weapons(gen)];

      m_times++;
      m_times_of_last_four_star++;
      m_times_of_last_five_star++;
      break;
  }

  return WISH_ERR;
}
}

