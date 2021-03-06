#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include "card.hpp"


class CardStack{
    private:
        std::vector<Card> cards;
        void shuffle();
    public:
        CardStack();
        CardStack(std::vector<Card>);
        Card pop();
        bool isEmpty();
        void setCardStack();
        void push_back(Card card);
        void addFourCardsToStack(int cardsCount, int counter, Effects effect);
        int getCardsCount();
};