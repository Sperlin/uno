#pragma once
#include <vector>
#include "card.hpp"

class PlayerCards {
    private:
        std::vector<Card> cards;
    public:
        void add_card(Card &card_from_stack);
        void get_card(std::string choice);
        PlayerCards();
        void print_cards();
        std::vector<Card> &getCards();
};
