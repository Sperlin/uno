#include "PlayedCards.hpp"

std::vector<Card> &PlayedCards::getPlayedCards() {
    return played_cards;
}

PlayedCards::PlayedCards() {
    std::vector<Card> cards;
    this->played_cards = cards;
}

void PlayedCards::save(Card &played_card) {
    this->played_cards.push_back(played_card);
}

Card &PlayedCards::top() {
    return played_cards[played_cards.size() - 1];
}

