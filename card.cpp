#include "card.hpp"

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
    //Normal card has no effects
    //Create new card in playerCards class:
    //  Try parsing the card from string to int, if doesn't work: create special card  
    Effects &Card::getEffect()
    {
        return this -> effect;
    }

    Card::Card(int Value, int Id, Colors Color, Effects Effect){
        value = Value;
        id = Id;
        color = Color;
        effect = Effect;
    }

