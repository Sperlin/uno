#pragma once
#include <vector>
#include "card.hpp"

class PlayedCards {
    private:
        std::vector<Card> played_cards;
    public:
        void save(Card &played_card);
        std::vector<Card> copy(std::vector<Card>);
        Card top();
        std::vector<Card> &getPlayedCards();
        PlayedCards();
};