//
// Created by Nathan on 12/29/2020.
//

#include "HighCardHeurPlayer.h"

Card HighCardHeurPlayer::Turn(bool start, Card startCard, bool heartOut, std::vector<std::shared_ptr<Player>> otherPlayers, bool blackOut, bool firstCard) {
    if(firstCard) {
        return FirstCardTurn();
    }
    if (start) {
        if (heartOut) {
            return TurnStartHeartOut(blackOut);
        } else {
            return TurnStartNoHeartOut(blackOut);
        }
    } else {
        if (HaveStart(startCard)) {
            return TurnNoStartHaveStart(startCard, blackOut);
        } else {
            return TurnNoStartNoHaveStart();
        }
    }
}

Card HighCardHeurPlayer::TurnStartHeartOut(bool blackOut) {
    // Create a default index with the first index as -1
    std::tuple<int,int> index(-1, 0);
    if(blackOut) {
        return TurnStartBlackOut();
    } else {
        // Loop through all suits
        for(int s = 0; s < cards.size(); s++) {
            // If the suit isn't a heart and (the suit isn't a spade or (the player has no spades or the player doesn't have a spade higher than a jack))
            if(s != 2 && (s != 3 ||(cards[3].size() > 0 && cards[3][0].Num() < 10))) {
                // If the index is still default, set the new index as the highest card of the suit we are on
                if(std::get<0>(index) == -1) {
                    if(cards[s].size() > 0) {
                        index = std::tuple<int,int>(s, 0);
                    }
                } else if(cards[s].size() > 0) {
                    // If the index is has been set already, check if the highest card of this suit is higher than the previous card
                    if(cards[std::get<0>(index)][0].Num() < cards[s][0].Num()) {
                        // If so, set the new highest card
                        index = std::tuple<int,int>(s,0);
                    }
                }
            }
        }
        // If we still haven't set a card, then we have no diamonds and no clubs
        if(std::get<0>(index) == -1 && cards[2].size() > 0) {
            // If we have a heart, set the card as the lowest heart
            index = std::tuple<int,int>(2,cards[2].size()-1);
        } else if(std::get<0>(index) == -1) {
            // If we only have spades, play our highest spade that's not the black mariah
            for (int c = 0; c < cards[3].size(); c++) {
                if(cards[3][c].Num() != 10) {
                    index = std::tuple<int, int>(3, c);
                    break;
                }
            }
            // If we have only the black mariah, play the black mariah
            if(std::get<0>(index) == -1) {
                index = std::tuple<int,int>(3,0);
            }
        }
        // Delete the card we chose and return it
        return DeleteCard(std::get<0>(index), std::get<1>(index));
    }
}

Card HighCardHeurPlayer::TurnStartNoHeartOut(bool blackOut) {
    std::tuple<int,int> index(-1, 0);
    if(blackOut) {
        return TurnStartBlackOut();
    } else {
        for(int s = 0; s < cards.size(); s++) {
            if(s != 2 && (s != 3 ||(cards[3].size() > 0 && cards[3][0].Num() < 10))) {
                if(std::get<0>(index) == -1) {
                    if(cards[s].size() > 0) {
                        index = std::tuple<int,int>(s, 0);
                    }
                } else if(cards[s].size() > 0) {
                    if(cards[std::get<0>(index)][0].Num() < cards[s][0].Num()) {
                        index = std::tuple<int,int>(s,0);
                    }
                }
            }
        }
        if(std::get<0>(index) == -1 && cards[3].size() > 0) {
            index = std::tuple<int,int>(3,0);
        } else if(std::get<0>(index) == -1) {
            index = std::tuple<int,int>(2,cards[2].size()-1);
        }
        return DeleteCard(std::get<0>(index), std::get<1>(index));
    }
}

Card HighCardHeurPlayer::TurnNoStartHaveStart(Card startCard, bool blackOut) {
    if (startCard.Suit() == 3 && !blackOut) {
        if (haveBlack) {
            for (int i = 0; i < cards[3].size(); i++) {
                if (cards[3][i].Num() != 10) {
                    return DeleteCard(3,i);
                }
            }
        } else {
            for (int i = 0; i < cards[3].size(); i++) {
                if (cards[3][i].Num() < 10) {
                    return DeleteCard(3,i);
                }
            }
        }
        return DeleteCard(3,0);
    }
    return DeleteCard(startCard.Suit(), 0);
}

Card HighCardHeurPlayer::TurnNoStartNoHaveStart() {
    if (haveBlack) {
        for (int i = 0; i < cards[3].size(); i++) {
            if (cards[3][i].Num() == 10) {
                return DeleteCard(3,i);
            }
        }
    }
    int suit = -1;
    if (cards[2].size() == 0) {
        for (int s = 0; s < cards.size(); s++) {
            if (cards[s].size() > 0) {
                if (suit == -1) {
                    suit = s;
                } else {
                    if (cards[suit][0].Num() < cards[s][0].Num()) {
                        suit = s;
                    }
                }
            }
        }
        return DeleteCard(suit, 0);
    }
    return DeleteCard(2,0);
}

Card HighCardHeurPlayer::TurnStartBlackOut() {
    std::tuple<int,int> index(-1,0);
    for(int s = 0; s < cards.size(); s++) {
        if(s != 2) {
            if(std::get<0>(index) == -1) {
                if(cards[s].size() > 0) {
                    index = std::tuple<int,int>(s, 0);
                }
            } else if(cards[s].size() > 0) {
                if(cards[std::get<0>(index)][0].Num() < cards[s][0].Num()) {
                    index = std::tuple<int,int>(s,0);
                }
            }
        }
    }
    if(std::get<0>(index) == -1) {
        index = std::tuple<int,int>(2,cards[2].size()-1);
    }
    int i0 = std::get<0>(index);
    int i1 = std::get<1>(index);
    Card turn = cards[i0][i1];
    cards[i0].erase(cards[i0].begin() + i1);
    return turn;
}

void HighCardHeurPlayer::PrintName(int p) {
    std::cout << "HighCardHeurPlayer #" << p;
}
