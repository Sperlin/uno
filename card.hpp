#pragma once
#include <string>
#include "Colors.cpp"
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
        Card();
        Card(int Value, int Id, Colors Color, Effects Effect);
        int &getValue();
        int &getId();
        Colors &getColor();
        Effects &getEffect();
        bool &getPlayable();
        void setColor(Colors color);
        void setPlayable(bool status);
};
