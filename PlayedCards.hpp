#pragma once
#include <vector>
#include "CardStack.hpp"

class PlayedCards {
    private:
        std::vector<Card> played_cards;
    public:
        PlayedCards();
        std::vector<Card> &getPlayedCards();
        void save(Card &played_card);
        Card &top();
        CardStack copy(std::vector<Card>);
};