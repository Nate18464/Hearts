//
// Created by Nathan on 8/17/2020.
//

#ifndef OH_SHIT_AI_BOARD_H
#define OH_SHIT_AI_BOARD_H
#include "Player.h"
#include "RanPlayer.h"
#include "HighCardHeurPlayer.h"
#include "MedHuerPlayer.h"
#include <iostream>

class Board {
private:
    std::vector<std::shared_ptr<Player>> players;
    Card startCard;
    bool heartOut;
    bool blackOut;
    void DealCards();
    void Play();
    void Win();
    void Reset();
    void IncrementCurPlayer(int& curPlayer);
    int RandNumGen(int start, int end);
    void SetStartPlayer(int &curPlayer);
    void GivePoints(std::vector<Card> cardsPlayed, int &curPlayer);
    bool GameContinue();
    std::vector<std::shared_ptr<Player>> GetOtherPlayers(int curPlayer);
    void ResetRound();
    void ShootTheMoon(int p);
    void PrintCard(Card card);
    void PrintPlayer(int p);
public:
    Board(std::vector<std::shared_ptr<Player>> players);
    void StartGame(int numRounds);
    void PrintWins();
};


#endif //OH_SHIT_AI_BOARD_H
