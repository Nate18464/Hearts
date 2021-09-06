//
// Created by Nathan on 8/17/2020.
//

#include "Player.h"

Player::Player():wins(0), points(0), totalpoints(0), haveBlack(false), start(false) {
    for (int c = 0; c < 4; c++) {
        cards.emplace_back(std::vector<Card>());
        numEachSuit.emplace_back(0);
    }
}

void Player::AddCard(Card card) {
    // Increment numEachSuit for the suit of the card
    numEachSuit[card.Suit()]++;
    // If the card is the black mariah, set haveBlack to true
    if (card.Suit() == 3 && card.Num() == 10) {
        haveBlack = true;
    }
    // If the card is the 2 of clubs, set start to true
    if (card.Suit() == 1 && card.Num() == 0) {
        start = true;
    }
    // If there are no cards of the suit in the player's hand, emplace back the card
    if (cards[card.Suit()].size() == 0) {
        cards[card.Suit()].emplace_back(card);
    } else {
        // Otherwise, insert the card so that the highest card for a suit is at index 0 and as the index increases, the cards have lower numbers
        int i;
        for(i = 0; i < cards[card.Suit()].size(); i++) {
            if (cards[card.Suit()][i].Num() < card.Num()) {
                break;
            }
        }
        cards[card.Suit()].insert(cards[card.Suit()].begin()+i, card);
    }
}

void Player::Reset() {
    totalpoints = 0;
}

void Player::AddWin() {
    wins++;
}

int Player::Wins() {
    return wins;
}

int Player::Points() {
    return points;
}

void Player::AddPoints(int p) {
    points += p;
}

void Player::AddTotalPoints(int p) {
    totalpoints += p;
}

int Player::TotalPoints() {
    return totalpoints;
}

void Player::ResetRound() {
    points = 0;
    haveBlack = false;
    start = false;
}

bool Player::HaveStart(Card startCard) {
    return cards[startCard.Suit()].size() > 0;
}

bool Player::Start() {
    return start;
}

Card Player::FirstCardTurn() {
    Card turn = cards[1][cards[1].size()-1];
    cards[1].erase(cards[1].begin()+cards[1].size()-1);
    return turn;
}

void Player::PrintCard(Card card) {
    card.PrintCard();
}

void Player::PrintCards() {
    for(auto& vec : cards) {
        for(auto& c : vec) {
            PrintCard(c);
            std::cout << std::endl;
        }
    }
}

bool Player::In(int i, std::vector<int> vec) {
    for(int c : vec) {
        if(c == i) {
            return true;
        }
    }
    return false;
}

Card Player::DeleteCard(int i0, int i1) {
    Card turn = cards[i0][i1];
    cards[i0].erase(cards[i0].begin()+i1);
    return turn;
}
