#pragma once
#include "player.hpp"

class Turn {
    private:
        Player current_player;
        Effects effect_from_previous_player;
        Card top_card;
    public:
        void turn();
        Player &getCurrentPlayer();
        Effects &getEffectFromPreviousPlayer();
        Card &getTopCard();
        void setCurrentPlayer(Player &player);
        void setEffectFromPreviousPlayer(Effects &effect);
        void setTopCard(Card &card);
        Turn(Player current_player, Effects effect_from_previous_player, Card top_card);
        Turn();
};