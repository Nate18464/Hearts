//
// Created by Nathan on 8/17/2020.
//

#ifndef OH_SHIT_AI_PLAYER_H
#define OH_SHIT_AI_PLAYER_H
#include "Card.h"

class Player {
protected:
    int wins;
    int totalpoints;
    int points;
    std::vector<std::vector<Card>> cards;
    bool start;
    bool haveBlack;
    bool HaveStart(Card startCard);
    Card FirstCardTurn();
    void PrintCard(Card card);
    std::vector<int> numEachSuit;
    bool In(int i, std::vector<int> vec);
    Card DeleteCard(int i0, int i1);
public:
    Player();
    void AddCard(Card card);
    virtual Card Turn(bool start, Card startCard, bool heartOut, std::vector<std::shared_ptr<Player>> otherPlayers, bool blackOut, bool firstCard) = 0;
    virtual void PrintName(int p) = 0;
    void Reset();
    void AddWin();
    int Wins();
    int Points();
    void AddPoints(int p);
    void ResetRound();
    void AddTotalPoints(int p);
    int TotalPoints();
    bool Start();
    void PrintCards();
};


#endif //OH_SHIT_AI_PLAYER_H
