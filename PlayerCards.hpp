#pragma once
#include <vector>
#include "card.hpp"

class PlayerCards {
    private:
        std::vector<Card> cards;
    public:
        PlayerCards();
        std::vector<Card> &getCards();
        void add_card(Card &card_from_stack);
        void print_cards();
        void setAllPlayable();
};
