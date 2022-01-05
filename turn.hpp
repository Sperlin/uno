#pragma once
#include "player.hpp"

class Turn {
    private:
        Player *current_player; /* needs to be a pointer in order to differentatiate between bot an real player*/
        Effects effect_from_previous_player;
        Card top_card;
        std::string direction;
        
    public:
        
        Turn();
        Turn(Player *current_player, Effects effect_from_previous_player, Card top_card, std::string current_direction);
        Player *getCurrentPlayer();
        Effects &getEffectFromPreviousPlayer();
        Card &getTopCard();
        std::string &getDirection();
        void setCurrentPlayer(Player &player);
        void setEffectFromPreviousPlayer(Effects &effect);
        void setTopCard(Card &card);
        void setDirection(std::string &direction);
        void changeDirection();
};