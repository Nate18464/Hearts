//
// Created by Nathan on 8/17/2020.
//

#include "Board.h"

Board::Board(std::vector<std::shared_ptr<Player>> players): players(players), heartOut(false), blackOut(false) {
}

void Board::StartGame(int numRounds) {
    for(int c = 0; c < numRounds; c++) {
        Play();
        Win();
        Reset();
    }
    PrintWins();
}

// Game loop for hearts
void Board::Play() {
    // Loop until a player has 100 or more points
    while(GameContinue()) {
        DealCards();
        int curPlayer;
        SetStartPlayer(curPlayer);
        std::vector<std::vector<Card>> allPrevCards = {};
        // Loop through 13 rounds
        for (int c = 0; c < 13; c++) {
            std::vector<Card> cardsPlayed = {};
            // Loop through each player's turn
            for (int i = 0; i < 4; i++) {
                //PrintPlayer(curPlayer);
                //std::cout << "and played:" << std::endl;
                if (i == 0 && c == 0) {
                    cardsPlayed.emplace_back(players[curPlayer]->Turn(true, Card(0), heartOut, GetOtherPlayers(curPlayer), blackOut,true));
                } else if (i == 0) {
                    cardsPlayed.emplace_back(players[curPlayer]->Turn(true,Card(0), heartOut, GetOtherPlayers(curPlayer), blackOut, false));
                } else {
                    cardsPlayed.emplace_back(players[curPlayer]->Turn(false, cardsPlayed[0], heartOut, GetOtherPlayers(curPlayer), blackOut, false));
                }
                //PrintCard(cardsPlayed[i]);
                IncrementCurPlayer(curPlayer);
            }
            // After each player has gone, give points to the winner
            GivePoints(cardsPlayed, curPlayer);
        }
        ResetRound();
    }
}

void Board::Win() {
    std::vector<int> winners = {0};
    for(int c = 1; c < players.size(); c++) {
        if(players[winners[0]]->TotalPoints() == players[c]->TotalPoints()) {
            winners.push_back(c);
        }
        else if(players[winners[0]]->TotalPoints() > players[c]->TotalPoints()) {
            winners = {c};
        }
    }
    for(int c : winners) {
        players[c]->AddWin();
    }
}

void Board::Reset() {
    for(int c = 0; c < players.size(); c++) {
        players[c]->Reset();
    }
}

// Deals the cards out to each player
void Board::DealCards() {
    // Start with a sorted deck of 52 cards
    std::vector<Card> deck = {};
    for(int c = 0; c < 52; c++) {
        deck.emplace_back(Card(c));
    }
    // Loop randomly choosing one card out of the deck to remove and add to a players hand
    for(int c = 51; c >= 0; c--) {
        int randnum = RandNumGen(0, deck.size()-1);
        players[(c)%players.size()]->AddCard(deck[randnum]);
        deck.erase(deck.begin()+randnum);
    }
}

void Board::PrintWins() {
    for(int c = 0; c < players.size(); c++) {
        std::cout << "Player " << c+1 << ": " << players[c]->Wins() << " wins\n";
    }
}

void Board::IncrementCurPlayer(int &curPlayer) {
    curPlayer++;
    if(curPlayer == players.size()) {
        curPlayer = 0;
    }
}

int Board::RandNumGen(int start, int end) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(start, end);
    return distr(eng);
}

// Randomly selects a player to start
void Board::SetStartPlayer(int &curPlayer) {
    for(int c = 0; c < players.size(); c++) {
        if (players[c]->Start()) {
            curPlayer = c;
            break;
        }
    }
}

// Gives the winner of the current round points and sets the starting player for the next round
void Board::GivePoints(std::vector<Card> cardsPlayed, int &curPlayer) {
    // Set by default the winner as the first player
    int winner = 0;
    // Loop through other players and see if they won the round
    for(int c = 1; c < 3; c++)  {
        if(cardsPlayed[c].Suit() == cardsPlayed[winner].Suit()) {
            if(cardsPlayed[c].Num() > cardsPlayed[winner].Num()) {
                winner = c;
            }
        }
    }
    for (int c = 0; c < winner; c++) {
        IncrementCurPlayer(curPlayer);
    }
    // Count the points the winner will recieve
    int points = 0;
    for (Card card : cardsPlayed) {
        if(card.Suit() == 2) {
            // If the card is a heart, add one point
            points ++;
            heartOut = true;
        } else if(card.Suit() == 3 && card.Num() == 10) {
            // If the card is the black mariah, add 13 points
            points += 13;
            heartOut = true;
            blackOut = true;
        }
    }
    // Add points to the winner
    players[curPlayer]->AddPoints(points);
}

// Checks whether any player has 100 or more points
bool Board::GameContinue() {
    for(auto& player: players) {
        if (player->TotalPoints() >= 100) {
            return false;
        }
    }
    return true;
}

// Returns a vector of pointers to all the players that aren't the current player
std::vector<std::shared_ptr<Player>> Board::GetOtherPlayers(int curPlayer) {
    std::vector<std::shared_ptr<Player>> otherPlayers = {};
    for(int c = 0; c < 3; c++) {
        IncrementCurPlayer(curPlayer);
        otherPlayers.emplace_back(players[curPlayer]);
    }
    return otherPlayers;
}

// Adds to the total points for each player and resets their points for the round
void Board::ResetRound() {
    bool moon = false;
    // Checks if someone got all hearts and black mariah
    for(int c = 0; c < 4; c++) {
        if(players[c]->Points() == 26) {
            ShootTheMoon(c);
            moon = true;
        }
    }
    // If nobody shot the moon, give people the points they recieved from the round
    if (!moon) {
        for (auto &player: players) {
            player->AddTotalPoints(player->Points());
        }
    }
    for(auto &player: players) {
        player->ResetRound();
    }
}

// Gives all players that did not shoot the moon 26 points
void Board::ShootTheMoon(int p) {
    for(int c = 0; c < 4; c++) {
        if(c != p) {
            players[c]->AddTotalPoints(26);
        }
    }
}

// Prints a specific card
void Board::PrintCard(Card card) {
    card.PrintCard();
    std::cout << std::endl;
}

// Prints the players name and says what cards they have
void Board::PrintPlayer(int p) {
    players[p]->PrintName(p);
    std::cout << " has these cards:" << std::endl;
    players[p]->PrintCards();
}
