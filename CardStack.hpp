#pragma once
#include <vector>
#include "card.hpp"

class CardStack{
    private:
        std::vector<Card> cards;
        void shuffle();
    
    public:
        CardStack();
        Card pop();
        bool isEmpty();
        std::vector<Card> getCards();
        void setCardStack();
        void setCardStack(std::vector<Card>);
        void addFourCardsToStack(int cardsCount, int counter, Effects effect);
        void printCards(); // FOR TESTING PURPOSES
};