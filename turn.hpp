#pragma once
#include "player.hpp"
#include "Effect.cpp"

class Turn {
    private:
        Player current_player;
        PlayerCards played_cards;
        Effects effect_from_previous_player;
    public:
        void turn(Player current_player);
};