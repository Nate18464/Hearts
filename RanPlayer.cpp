//
// Created by Nathan on 12/29/2020.
//

#include "RanPlayer.h"

Card RanPlayer::Turn(bool start, Card startCard, bool heartOut, std::vector<std::shared_ptr<Player>> otherPlayers, bool blackOut, bool firstCard) {
    if (firstCard) {
        return FirstCardTurn();
    }
    std::vector<std::tuple<int,int>> possibleCardsIndexes;
    for(int c = 0; c < 4; c++) {
        for(int i = 0; i < cards[c].size(); i++) {
            if (start) {
                if (heartOut) {
                    // Add the card as possible if the player starts and has a heart out because then the player can start with any card
                    possibleCardsIndexes.emplace_back(std::tuple<int,int>(c,i));
                } else {
                    if (c != 2) {
                        // If the player is starting, but there hasn't been a heart yet, then only add cards that aren't hearts to the possible starting cards
                        possibleCardsIndexes.emplace_back(std::tuple<int,int>(c,i));
                    }
                }
            } else {
                if(cards[startCard.Suit()].size() == 0) {
                    // If the player is not starting, but doesn't have any cards that match the starting suit, the player can play any card
                    possibleCardsIndexes.emplace_back(std::tuple<int,int>(c,i));
                } else if(c == startCard.Suit()) {
                    // If the player is not starting, and has cards that match with the starting suit, the player can only play cards of the starting suit
                    possibleCardsIndexes.emplace_back(std::tuple<int,int>(c,i));
                }
            }
        }
    }
    // Get a random number
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, possibleCardsIndexes.size()-1);
    int ranNum = distr(eng);
    // Set i0 and i1 to indexes from the possibleCardsIndexes based on the random number generated
    int i0 = std::get<0>(possibleCardsIndexes[ranNum]);
    int i1 = std::get<1>(possibleCardsIndexes[ranNum]);
    return DeleteCard(i0, i1);
}

void RanPlayer::PrintName(int p) {
    std::cout << "RanPlayer #" << p;
}
