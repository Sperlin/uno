#pragma once
#include <vector>
#include "card.hpp"

class CardStack{
    private:
        std::vector<Card> cards;
        void shuffle();
    
    public:
        Card pop();
        bool isEmpty();
        void setCardStack();
        void setCardStack(std::vector<Card>);
        void addFourCardsToStack(int cardsCount, int counter, Effects effect);
        void printCards();
        CardStack();
};