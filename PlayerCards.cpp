#include <vector>
#include <iostream>
#include "PlayerCards.hpp"

PlayerCards::PlayerCards() {
    std::vector<Card> cards;
    this->cards = cards;
}

void PlayerCards::add_card(Card &card_from_stack) {
    cards.push_back(card_from_stack);
}

void PlayerCards::print_cards() {
    std::cout << "Player Cards:" << std::endl;
    for (Card card : this->cards) {
        std::cout << card.getId() << std::endl;
    }
}

std::vector<Card> &PlayerCards::getCards() {
    return cards;
}

void PlayerCards::setAllPlayable() {
    for (Card &card : cards) {
        card.setPlayable(false);
    }
}