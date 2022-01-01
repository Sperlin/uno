#pragma once
#include <iostream>
#include <regex>
#include "turn.hpp"
#include "CardStack.hpp"
#include "PlayedCards.hpp"

class Game {
    private:
        Turn current_turn;
        std::vector<Player*> players;
        Effects played_effect;
        CardStack card_stack;
        PlayedCards played_cards;
    public:
        void startGame();
        void runGame();
        void nextTurn(Effects &played_effect);
        void win(Turn &current_turn);
        Game();
        void printCard(Card &card);
        void printTopCard();
        void printCardsInHand();
        std::string getInput();
};