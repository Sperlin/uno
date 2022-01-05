#pragma once
#include "player.hpp"

class Turn {
    private:
        Player *current_player; /* needs to be a pointer in order to differentatiate between bot an real player*/
        Effects effect_from_previous_player;
        Card top_card;
    public:
        int cards_to_add;
        std::string direction;
        Turn();
        Turn(Player *current_player, Effects effect_from_previous_player, int cards_to_add, Card top_card, std::string direction);
        Player *getCurrentPlayer();
        Card &getTopCard();
        Effects &getEffectFromPreviousPlayer();
        void setCurrentPlayer(Player &player);
        void setTopCard(Card &card);
        void changeDirection();
        int &getCardsToAdd();
        void setCardsToAdd(int cards_count);
        void addToCardsCounter(int count);
        Card changeTopCardEffect(Effects effect);
};