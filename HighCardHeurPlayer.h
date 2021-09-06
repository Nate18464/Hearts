//
// Created by Nathan on 12/29/2020.
//

#ifndef HEARTS_HIGHCARDHEURPLAYER_H
#define HEARTS_HIGHCARDHEURPLAYER_H
#include "Player.h"

class HighCardHeurPlayer : public Player {
private:
    Card TurnStartBlackOut();
    Card TurnStartHeartOut(bool blackOut);
    Card TurnStartNoHeartOut(bool blackOut);
    Card TurnNoStartHaveStart(Card startCard, bool blackOut);
    Card TurnNoStartNoHaveStart();
public:
    virtual Card Turn(bool start, Card startCard, bool heartOut, std::vector<std::shared_ptr<Player>> otherPlayers, bool blackOut, bool firstCard);
    virtual void PrintName(int p);
};


#endif //HEARTS_HIGHCARDHEURPLAYER_H
