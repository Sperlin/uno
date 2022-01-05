#include "turn.hpp"

Turn::Turn() {};

Turn::Turn(Player *current_player, Effects effect_from_previous_player, int cards_to_add, Card top_card, std::string direction) {
    this->current_player = current_player;
    this->effect_from_previous_player = effect_from_previous_player;
    this->cards_to_add = cards_to_add;
    this->top_card = top_card;
    this->direction = direction;
};

Player* Turn::getCurrentPlayer() {
    return current_player;
}

Card &Turn::getTopCard() {
    return top_card;
}
Card Turn::changeTopCardEffect(Effects effect){
    this->top_card.setEffect(effect);
    return this->top_card;
}
void Turn::setCardsToAdd(int cards_count){
    this->cards_to_add = cards_count;
} 

int &Turn::getCardsToAdd(){
    return cards_to_add;
}
void Turn::addToCardsCounter(int count){
    this->cards_to_add += count; 
}
Effects &Turn::getEffectFromPreviousPlayer(){
    return effect_from_previous_player;
}
void Turn::changeDirection(){
    if(this->direction == "clockwise"){
        this->direction = "counterclockwise";
    }
    else if(this->direction == "counterclockwise"){
        this->direction = "clockwise";
    }
}
