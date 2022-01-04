#include "turn.hpp"

Turn::Turn() {};

Turn::Turn(Player *current_player, Effects effect_from_previous_player, Card top_card) {
    this->current_player = current_player;
    this->effect_from_previous_player = effect_from_previous_player;
    this->top_card = top_card;
    this->direction = "clockwise";
};

Player* Turn::getCurrentPlayer() {
    return current_player;
}

Card &Turn::getTopCard() {
    return top_card;
}
Effects &Turn::getEffectFromPreviousPlayer(){
    return effect_from_previous_player;
}
void changeDirection(){
    if(this->direction == "clockwise"){
        this->direction = "counterclockwise";
    }
    else if(this->direction == "counterclockwise"){
        this->direction = "clockwise";
    }
}