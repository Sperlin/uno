#include "turn.hpp"

Turn::Turn(Player *current_player, Effects effect_from_previous_player, Card top_card) {
    this->current_player = current_player;
    this->effect_from_previous_player = effect_from_previous_player;
    this->top_card = top_card;
};

Turn::Turn() {};

Card &Turn::getTopCard() {
    return top_card;
}

Player* Turn::getCurrentPlayer() {
    return current_player;
}