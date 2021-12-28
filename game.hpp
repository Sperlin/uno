#pragma once
#include "turn.hpp"

class Game {
    private:
        Turn current_turn;
        std::vector<Player> players;
        Effects played_effect;
    public:
        void startMenu();
        void startGame();
        void nextTurn(Effects played_effect);
        void win(Turn current_turn);
};