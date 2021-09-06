//
// Created by Nathan on 1/14/2021.
//

#include "MedHuerPlayer.h"

Card MedHuerPlayer::Turn(bool start, Card startCard, bool heartOut, std::vector<std::shared_ptr<Player>> otherPlayers,
                         bool blackOut, bool firstCard) {
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

void MedHuerPlayer::PrintName(int p) {
    std::cout << "MedHeurPlayer #" << p;
}

Card MedHuerPlayer::TurnNoStartHaveStart(Card startCard, bool blackOut) {
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
    return DeleteCard(startCard.Suit(),0);
}

Card MedHuerPlayer::TurnNoStartNoHaveStart() {
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

Card MedHuerPlayer::TurnStartNoHeartOut(bool blackOut) {
    if(blackOut) {
        return TurnStartBlackOut();
    }
    std::vector<int> prio = StartPrio();
    for(int c = 0; c < 4; c++) {
        if(prio[c] != 2 && (prio[c] != 3 || cards[3][0].Num() < 10)) {
            if (cards[prio[c]].size() > 0) {
                return DeleteCard(prio[c], 0);
            }
        }
    }
    if(cards[3].size() > 0) {
        for(int c = 0; c < cards[3].size(); c++) {
            if(cards[3][c].Num() != 10) {
                return DeleteCard(3,c);
            }
        }
        return DeleteCard(3,0);
    }
    return DeleteCard(2,cards[2].size()-1);
}

Card MedHuerPlayer::TurnStartHeartOut(bool blackOut) {
    if(blackOut) {
        return TurnStartBlackOut();
    }
    std::vector<int> prio = StartPrio();
    std::tuple<int,int> index(-1, 0);
    for(int c = 0; c < 4; c++) {
        if(prio[c] != 3 || cards[3][0].Num() < 10) {
            if (cards[prio[c]].size() > 0 && prio[c] != 2) {
                return DeleteCard(prio[c],0);
            } else if (cards[prio[c]].size() > 0) {
                return DeleteCard(prio[c], cards[prio[c]].size()-1);
            }
        }
    }
    if(cards[3].size() > 0) {
        for(int c = 0; c < cards[3].size(); c++) {
            if(cards[3][c].Num() != 10) {
                return DeleteCard(3,c);
            }
        }
        return DeleteCard(3,0);
    }
    return DeleteCard(2,cards[2].size()-1);
}

Card MedHuerPlayer::TurnStartBlackOut() {
    std::vector<int> prio = StartPrio();
    for(int c = 0; c < 4; c++) {
        if(cards[prio[c]].size() > 0 && prio[c] != 2) {
            return DeleteCard(prio[c], 0);
        } else if(cards[prio[c]].size() > 0) {
            return DeleteCard(prio[c], cards[prio[c]].size()-1);
        }
    }
}

std::vector<int> MedHuerPlayer::StartPrio() {
    std::vector<int> prio = {};
    for(int c = 0; c < 4; c++) {
        int min;
        for(int i = 0; i < 4; i++) {
            if(!In(i, prio)) {
                min = i;
                break;
            }
        }
        for(int i = 0; i < 4; i++) {
            if(!In(i, prio) && numEachSuit[i] < numEachSuit[min]) {
                min = i;
            }
        }
        prio.emplace_back(min);
    }
    return prio;
}
