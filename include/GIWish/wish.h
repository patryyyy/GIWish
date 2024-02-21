#ifndef WISH_H
#define WISH_H

#include <vector>
#include <random>
#include <ctime>

namespace GIWish {
const int UP = 0;
const int STANDARD = 1;
const int WEAPONS = 0;
const int CHARACTERS = 1;
const int WISH_OK = 1;
const int WISH_ERR = 0;

enum Level {
  FIVE_STAR,
  FOUR_STAR,
  THREE_STAR
};

struct WishInfo {
  std::time_t time;
  std::string format_time;
  std::string name;
  Level level;
};

struct WishHistory {
  std::vector<WishInfo> wh;
};

const std::string five_star_up_characters{"闲云"};

const std::vector<std::string> five_star_characters{
    "提纳里",
    "莫娜",
    "迪卢克",
    "迪希雅",
    "刻晴",
    "七七",
    "琴"
};

const std::vector<std::string> four_star_up_characters{
    "嘉明",
    "珐露珊",
    "诺艾尔"
};

const std::vector<std::string> four_star_characters{
    "夏沃蕾",
    "夏洛蒂",
    "菲米尼",
    "琳妮特",
    "卡维",
    "米卡",
    "瑶瑶",
    "莱依拉",
    "坎蒂丝",
    "多莉",
    "柯莱",
    "久岐忍",
    "云堇",
    "绮良良",
    "鹿野院平藏",
    "九条裟罗",
    "五郎",
    "早柚",
    "托马",
    "烟绯",
    "罗莎莉亚",
    "辛焱",
    "砂糖",
    "迪奥娜",
    "重云",
    "班尼特",
    "菲谢尔",
    "凝光",
    "行秋",
    "北斗",
    "香菱",
    "雷泽",
    "芭芭拉"
};

const std::vector<std::string> four_star_weapons{
    "弓藏",
    "祭礼弓",
    "绝弦",
    "西风猎弓",
    "昭心",
    "祭礼残章",
    "流浪乐章",
    "西风秘典",
    "西风长枪",
    "匣里灭辰",
    "雨裁",
    "祭礼大剑",
    "钟剑",
    "西风大剑",
    "匣里龙吟",
    "祭礼剑",
    "笛剑",
    "西风剑"
};

const std::vector<std::string> three_star_weapons{
    "弹弓",
    "神射手之誓",
    "鸦羽弓",
    "翡玉法球",
    "讨龙英杰谭",
    "魔导绪论",
    "黑缨枪",
    "以理服人",
    "沐浴龙血的剑",
    "铁影阔剑",
    "飞天御剑",
    "黎明神剑",
    "冷刃"
};

//WishInfo wish(std::random_device& rd, double five_star_probability, double four_star_probability, double three_star_probability, AllWishInfo& all_wish_info);
class WishManager {
 private:
  double m_five_star_probability;
  double m_four_star_probability;
  double m_three_star_probability;
  int m_times;
  int m_times_of_last_five_star;
  int m_times_of_last_four_star;
  bool m_is_get_standard_five_star;
  bool m_is_get_standard_four_star;

 public:
  WishManager(double five_star_probability,
              double four_star_probability,
              double three_star_probability,
              int times,
              int times_of_last_five_star,
              int times_of_last_four_star,
              bool is_get_standard_five_star,
              bool is_get_standard_four_star);
  int wish(WishInfo &wish_info);
};

}

#endif //WISH_H
