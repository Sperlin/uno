#pragma once
#include "turn.hpp"
#include "CardStack.hpp"
#include "PlayedCards.hpp"

class Game {
    private:
        Turn current_turn;
        std::vector<Player> players;
        Effects played_effect;
        CardStack card_stack;
        PlayedCards played_cards;
    public:
        void startMenu();
        void startGame();
        void nextTurn(Effects played_effect);
        void win(Turn current_turn);
        Game();
};