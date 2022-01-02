#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "PlayerCards.hpp"
#include "CardStack.hpp"
#include "PlayedCards.hpp"



class Player {
    protected:
        PlayerCards player_cards;
        int player_value;
    public:
        void possible_cards(Card &top_card);
        void draw(CardStack &card_stack, int amount);
        Card virtual *play(std::string choice, Card &top_card);
        void erase_played_card(Card *card_to_erase);
        void skip();
        Player();
        Player(int value);
        PlayerCards &getPlayerCards();
        int &getPlayerValue();
        Colors getColorOfInputCard(std::string color_string);
        int getValueOfInputCard(std::string value_string);
};

class RealPlayer : public Player {
    public:
        Card virtual *play(std::string choice, Card &top_card) override;
        RealPlayer(int value);
};

class Bot : public Player {
    public:
        Card virtual *play(std::string choice, Card &top_card) override;
        Bot(int value);
};


