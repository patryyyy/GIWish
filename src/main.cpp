#include <iostream>
#include <GIWish/cmdline/cmdline.h>
#include <GIWish/wish.h>

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int argc, char **argv) {
#ifdef _WIN32
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);
#endif

  cmdline::parser parser;
  parser.add<double>("pfive", '\0', "5-star item basic probability", false, 0.6, cmdline::range(0.0, 100.0));
  parser.add<double>("pfour", '\0', "4-star item basic probability", false, 5.1, cmdline::range(0.0, 100.0));
  parser.add<double>("pthree", '\0', "3-star item basic probability", false, 94.3, cmdline::range(0.0, 100.0));
  parser.add<int>("times", 't', "Times of per round of wishing", false, 10);
  parser.add("version", 'v', "Version information");

  parser.parse_check(argc, argv);

  if (parser.exist("version")) {
    std::cout << "GIWish 1.0" << std::endl;
    return 0;
  }

  GIWish::WishManager wish_manager
      {parser.get<double>("pfive"), parser.get<double>("pfour"), parser.get<double>("pthree"), 0, 0, 0, false, false};
  GIWish::WishInfo wish_info;

  while (true) {
    START_WISH:

    for (int i = 0; i < parser.get<int>("times"); ++i) {
      wish_manager.wish(wish_info);
      switch (wish_info.level) {
        case GIWish::FIVE_STAR:
          std::printf("Level: %s\t Name: %s\n", "★★★★★", wish_info.name.c_str());
          break;
        case GIWish::FOUR_STAR:
          std::printf("Level: %s\t Name: %s\n", "★★★★", wish_info.name.c_str());
          break;
        case GIWish::THREE_STAR:
          std::printf("Level: %s\t Name: %s\n", "★★★", wish_info.name.c_str());
          break;
      }
    }

    std::cout << "Enter to continue wishing...";

    int c = std::cin.get();
    if (c == '\n') {
      goto START_WISH;
    } else {
      exit(0);
    }
  }
}
