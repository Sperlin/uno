#pragma once
#include "Colors.cpp"
#include <string>
#include "Effect.cpp"

class Card
{
    //enum class Colors {Blue, Green, Red, Yellow};
    private:
        int value;
        int id;
        Colors color;
        Effects effect;
        bool playable;
    public:
        Card(int Value, int Id, Colors Color, Effects Effect);
        int &getValue();
        int &getId();
        Colors &getColor();
        void setColor(Colors color);
        Effects &getEffect();
        bool &getPlayable();
        void setPlayable(bool status);
        Card();
};
