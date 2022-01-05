#include "card.hpp"

    Card::Card(){}

    Card::Card(int Value, int Id, Colors Color, Effects Effect){
        value = Value;
        id = Id;
        color = Color;
        effect = Effect;
        playable = false;
    }
    
    int &Card::getValue()
    {
        return this -> value; 
    }

    int &Card::getId()
    {
        return this -> id;
    }

    Colors &Card::getColor()
    {
        return this -> color;
    }
    
    Effects &Card::getEffect()
    {
        return this -> effect;
    }

    bool &Card::getPlayable() {
        return this -> playable;
    }

    void Card::setColor(Colors color) {
        this->color = color;
    }

    void Card::setPlayable(bool status) {
        this->playable = status;
    }
    void Card::setEffect(Effects effect){
        this->effect = effect;
    }

