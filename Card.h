//
// Created by Nathan on 8/14/2020.
//

#ifndef OH_SHIT_AI_CARD_H
#define OH_SHIT_AI_CARD_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <fstream>
#include <tuple>
#include <math.h>

class Card {
private:
    int suit;
    int num;
    int value;
    std::vector<std::string> suits;
    std::vector<std::string> nums;
public:
    Card() = default;
    Card(int val);
    int Val();
    int Suit();
    int Num();
    void PrintCard();
};


#endif //OH_SHIT_AI_CARD_H
