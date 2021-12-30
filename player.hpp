#pragma once
#include <vector>
#include "card.hpp"
#include "PlayerCards.hpp"
#include "CardStack.hpp"

class Player {
    protected:
        PlayerCards player_cards;
    public:
        std::vector<Card> possible_cards(Card &top_card);
        void draw(CardStack &card_stack, int amount);
        bool virtual play(std::string choice);
        void skip();
        Player();
        PlayerCards &getPlayerCards();
};

class RealPlayer : public Player {
    public:
        bool virtual play(std::string choice) override;
        RealPlayer();
};

class Bot : public Player {
    public:
        bool virtual play(std::string choice) override;
        Bot();
};


