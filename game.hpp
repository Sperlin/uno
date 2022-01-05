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
        Game();
        void startGame();
        void runGame();
        bool nextTurn(Effects &played_effect);
        void win(Turn &current_turn);
        Player* nextPlayer();
        Player* nextPlayerReverse();
        void printCard(Card &card);
        void printTopCard();
        void printCardsInHand();
        std::string getInput();
        Colors colorChoice(int playerId);
};