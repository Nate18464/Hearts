#include "Board.h"


void makePlayers(std::vector<std::shared_ptr<Player>>& players) {
    players.emplace_back(std::shared_ptr<Player>(new MedHuerPlayer));
    players.emplace_back(std::shared_ptr<Player>(new MedHuerPlayer));
    players.emplace_back(std::shared_ptr<Player>(new MedHuerPlayer));
    players.emplace_back(std::shared_ptr<Player>(new RanPlayer));
}

int main() {
    std::vector<std::shared_ptr<Player>> players = {};
    makePlayers(players);
    Board board(players);
    board.StartGame(1000);
}
