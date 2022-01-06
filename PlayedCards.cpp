#include "PlayedCards.hpp"

PlayedCards::PlayedCards() {
    std::vector<Card> cards;
    this->played_cards = cards;
}

std::vector<Card> &PlayedCards::getPlayedCards() {
    return played_cards;
}

void PlayedCards::save(Card &played_card) {
    this->played_cards.push_back(played_card);
}

Card &PlayedCards::top() {
    return played_cards[played_cards.size() - 1];
}

CardStack PlayedCards::copy(std::vector<Card> cards){
    CardStack card_stack = CardStack(cards);
    this->played_cards.clear(); 
    return card_stack;
}
