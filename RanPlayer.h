//
// Created by Nathan on 12/29/2020.
//

#ifndef OH_SHIT_AI_RANPLAYER_H
#define OH_SHIT_AI_RANPLAYER_H
#include "Player.h"

class RanPlayer : public Player {
public:
    virtual Card Turn(bool start, Card startCard, bool heartOut, std::vector<std::shared_ptr<Player>> otherPlayers, bool blackOut, bool firstCard);
    virtual void PrintName(int p);
};


#endif //OH_SHIT_AI_RANPLAYER_H
