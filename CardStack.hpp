#pragma once
#include <vector>
#include "card.cpp"

class CardStack{
    private:
        std::vector<Card> cards;
        void shuffle();
    
    public:
        Card pop();
        bool isEmpty();
        void setCardStack();
        void setCardStack(std::vector<Card>);
        void CardStack::addFourCardsToStack(int cardsCount, int counter, Effects effect);
};