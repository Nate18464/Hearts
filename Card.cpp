//
// Created by Nathan on 8/14/2020.
//

#include "Card.h"

Card::Card(int val) {
    value = val;
    num = (val/4);
    suit = (val%4);
    // String values for purposes of printing the cards
    suits = {"Diamonds", "Clubs", "Hearts", "Spades"};
    nums = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
}

int Card::Val() {
    return value;
}

int Card::Suit() {
    return suit;
}

int Card::Num() {
    return num;
}

void Card::PrintCard() {
    std::cout << nums[Num()] << " of " << suits[Suit()];
}
