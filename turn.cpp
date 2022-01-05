#include "turn.hpp"

Turn::Turn() {};

Turn::Turn(Player *current_player, Effects effect_from_previous_player, Card top_card, std::string current_direction) {
    this->current_player = current_player;
    this->effect_from_previous_player = effect_from_previous_player;
    this->top_card = top_card;
    this->direction = current_direction;
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

std::string &Turn::getDirection() {
    return direction;
}

void Turn::setDirection(std::string &direction) {
    this->direction = direction;
}

void Turn::changeDirection(){
    if(this->direction == "clockwise"){
        this->direction = "counterclockwise";
    }
    else if(this->direction == "counterclockwise"){
        this->direction = "clockwise";
    }
}