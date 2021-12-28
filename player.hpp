#pragma once
#include "card.hpp"
#include "PlayerCards.hpp"
#include <vector>

class Player {
    protected:
        PlayerCards player_cards;
    public:
        std::vector<Card> possible_cards(Card top_card);
        Card draw();
        bool virtual play(std::string choice);
        void skip();
};

class RealPlayer : public Player {};

class Bot : public Player {
    public:
        bool virtual play(std::string choice) override;
};


