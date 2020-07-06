#include "Helper.h"

int gen_rand_num(int min, int max) {
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(min, max);

  return distr(eng);
}


