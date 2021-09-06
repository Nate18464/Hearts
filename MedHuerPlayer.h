//
// Created by Nathan on 1/14/2021.
//

#ifndef HEARTS_MEDHUERPLAYER_H
#define HEARTS_MEDHUERPLAYER_H
#include "Player.h"

class MedHuerPlayer : public Player {
private:
    Card TurnStartBlackOut();
    Card TurnStartHeartOut(bool blackOut);
    Card TurnStartNoHeartOut(bool blackOut);
    Card TurnNoStartHaveStart(Card startCard, bool blackOut);
    Card TurnNoStartNoHaveStart();
    std::vector<int> StartPrio();
public:
    virtual Card Turn(bool start, Card startCard, bool heartOut, std::vector<std::shared_ptr<Player>> otherPlayers, bool blackOut, bool firstCard);
    virtual void PrintName(int p);
};


#endif //HEARTS_MEDHUERPLAYER_H
