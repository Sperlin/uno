#pragma once
#include <vector>
#include <string>
#include "PlayerCards.hpp"
#include "CardStack.hpp"
#include "PlayedCards.hpp"



class Player {
    protected:
        PlayerCards player_cards;
        int player_value;
        std::string player_name;
    public:
        Player();
        Player(int value, std::string name);
        PlayerCards &getPlayerCards();
        int &getPlayerValue();
        std::string &getPlayerName();
        Card virtual *play(std::string choice, Card &top_card);
        int possible_cards(Card &top_card, bool cardPlayed);
        void draw(CardStack &card_stack, int amount);
        void erase_played_card(Card *card_to_erase);
        Colors getColorOfInputCard(std::string color_string);
        int getValueOfInputCard(std::string value_string);
        void skip();
};

class RealPlayer : public Player {
    public:
        Card virtual *play(std::string choice, Card &top_card) override;
        RealPlayer(int value, std::string name);
};

class Bot : public Player {
    public:
        Card virtual *play(std::string choice, Card &top_card) override;
        Bot(int value, std::string name);
};


