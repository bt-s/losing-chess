#ifndef HELPER_H
#define HELPER_H

#include <random>
#include <iterator>

int gen_rand_num(int min, int max);

enum Type {king, queen, bishop, knight, rook, pawn};

// Found the following two templates on StackOverflow:
// - https://stackoverflow.com/questions/6942273/how-to-get-a-random-
//   element-from-a-c-container
template<typename Iter, typename RandomGenerator>
Iter select_random_element(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_random_element(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_random_element(start, end, gen);
}

#endif
