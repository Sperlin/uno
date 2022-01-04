#pragma once
#include "player.hpp"

class Turn {
    private:
        Player *current_player; /* needs to be a pointer in order to differentatiate between bot an real player*/
        Effects effect_from_previous_player;
        Card top_card;
        
    public:
        std::string direction;
        Turn();
        Turn(Player *current_player, Effects effect_from_previous_player, Card top_card);
        Player *getCurrentPlayer();
        Effects &getEffectFromPreviousPlayer();
        Card &getTopCard();
        void setCurrentPlayer(Player &player);
        void setEffectFromPreviousPlayer(Effects &effect);
        void setTopCard(Card &card);
};