#pragma once
#include <iostream>
#include <regex>
#include <unistd.h>
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
        bool nextTurn(Effects &played_effect);
        Player* nextPlayer();
        Player* nextPlayerReverse();
        void win(Turn &current_turn);
        Game();
        void printCard(Card &card);
        void printTopCard();
        void printCardsInHand();
        std::string getInput();
};