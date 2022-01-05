#include "CardStack.hpp"
#include <algorithm>
#include <random>
#include <iostream>

CardStack::CardStack() {
    std::vector<Card> cards;
    this->cards = cards;
    setCardStack();
}
void CardStack::push_back(Card card){
    this->cards.push_back(card);
}

Card CardStack::pop()
{
    Card topCard = cards.front();
    cards.erase(cards.begin());

    return topCard;
}
bool CardStack::isEmpty()
{
    if(cards.empty()){
        return true;
    }
    return false;
}

void CardStack::shuffle()
{
    std::random_device rd;
    std::mt19937 e2(rd());

    auto rng = std::default_random_engine { e2() };

    std::shuffle(cards.begin(), cards.end(), rng);

}
//use in constructor?


void CardStack::setCardStack()
{
    //Add 0-9
    int cardValue = 0;
    int cardsCount = 0;
    for(cardsCount; cardsCount < 76; cardsCount += 4)
    {
        if(cardValue == 9){
            cardValue = 0;
        }
        addFourCardsToStack(cardValue, cardsCount, Effects::noEffect);
        cardValue++;
    }

    while(cardsCount < 100){

        addFourCardsToStack(10, cardsCount, Effects::draw2);
        cardsCount +=4 ;

        addFourCardsToStack(11, cardsCount, Effects::reverse);
        cardsCount +=4 ;

        addFourCardsToStack(12, cardsCount, Effects::skip);
        cardsCount +=4 ;
    }
    for(int i = 0; i < 8; i += 2)
    {
        cards.push_back(Card(13, cardsCount, Colors::Black, Effects::wildDraw4));
        cardsCount++;
        cards.push_back(Card(14, cardsCount, Colors::Black, Effects::wild));
        cardsCount++;
    }

    //Shuffle a couple of times to get everything random 
    for(int i = 0; i < 100; i++)
    {
        shuffle();
    }
}

void CardStack::addFourCardsToStack(int cardValue, int cardsCount, Effects effect)
{
    cards.push_back(Card(cardValue, cardsCount, Colors::Blue, effect));
    cards.push_back(Card(cardValue, cardsCount+1, Colors::Green, effect));
    cards.push_back(Card(cardValue, cardsCount+2, Colors::Red, effect));
    cards.push_back(Card(cardValue, cardsCount+3, Colors::Yellow, effect));
}

void CardStack::setCardStack(std::vector<Card>)
{

}

void CardStack::printCards() {
    std::cout << this->cards.size() << std::endl;
    for (Card card : this->cards) {
        std::cout << card.getId() << std::endl;
    }
}
