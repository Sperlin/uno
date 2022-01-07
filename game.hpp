#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>
#include <regex>
#include <string>
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
        bool nextTurn(Effects &effect_for_next_turn);
        void win(Turn &current_turn);
        Player* nextPlayer();
        Player* nextPlayerReverse();
        void printCard(Card &card);
        void printTopCard();
        void printCardsInHand();
        void printGameTable();
        std::string getInput();
        Colors colorChoice(int playerId);
        std::string parseEffect(Effects effect);
};