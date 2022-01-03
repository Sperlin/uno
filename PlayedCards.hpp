#pragma once
#include <vector>
#include "card.hpp"

class PlayedCards {
    private:
        std::vector<Card> played_cards;
    public:
        PlayedCards();
        std::vector<Card> &getPlayedCards();
        void save(Card &played_card);
        Card &top();
        std::vector<Card> copy(std::vector<Card>);
};