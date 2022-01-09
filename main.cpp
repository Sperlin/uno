#include <iostream>
#include "game.hpp"

void show_rules() {
    bool rules = true;
    while (rules) {
        std::cout << "\33[2J";
        std::cout << "Welcome to the game of UNO!" << std::endl
        << "Here is how this game works: " << std::endl
        << "You and 1 to 3 bots sit around a table with an UNO card stack containing a total of 108 cards." << std::endl
        << "Each card has a value between 0-9 and a color (blue, red, green, yellow, black). Some cards have special effects which will be explained later." << std::endl
        << "In the beginning each player draws 7 cards from the card stack and one card from the stack is put in the middle of the table." << std::endl
        << "The game starts with your turn and goes clockwise." << std::endl
        << "During a turn you are able to take a card from the hand and put it on top of the card in the middle." << std::endl
        << "However the card needs to match the value/effect or the color of the card in the middle. After a card has been played, it's the next players turn" << std::endl
        << "If there are no possible cards to play in your hand, you have to draw a card from the card stack. If you are still not able to play a card after drawing, it's the next players turn" << std::endl
        << "The goal is to be the first with no more cards in your hand" << std::endl
        << "\n Effect Cards: " << std::endl
        << "Some cards trigger special effects after they were played." << std::endl
        << "Reverse Card (&): After a Reverse Card has been played the turn order will be reversed." << std::endl
        << "Skip Card (/): After a Skip Card has been played, the next players turn will be skipped. However if the next player also has a Skip Card, it will get played aswell and the effect will carry on to the next player." << std::endl
        << "Draw2 Card (+2): After a Draw2 has been played, the next player has to draw 2 cards and their turn will get skipped. However the next player can 'stack' another Draw2 or Draw4 card on top of it, the amount of cards that have to be drawn add up and the effect will carry on to the next player." << std::endl
        << "Those three cards come in blue, red, green and yellow. The next two special effect cards are the only cards that are black and they only come in black." << std::endl
        << "Wild Card (#): After a Wild Card has been played, the current player can choose it's color." << std::endl
        << "Draw4 Card (+4): After a Draw4 Card has been played, the current player can choose it's color and the next player has to draw 4 cards and their turn will be skipped. Draw4 cards can also be stacked with Draw2 and other Draw4 cards." << std::endl;
        std::cout << "\nEnter 0 to go back to the menu screen: ";
        int input;
        std::cin >> input;
        switch(input) {
            case 0:
            rules = false;
            break;
            default:
            rules = true;
            break;
        }
    }   
}

int main() {
    bool menu = true;
    while (menu) {
        std::cout << "\33[2J";
        std::cout << "Welcome to the main menu!\n" << std::endl
    << "\t 1) Start a new game!" << std::endl 
    << "\t 2) Check the rules" << std::endl
    << "\t 3) Close the application" << std::endl;
    std::cout << "\nPlease select from one of the following by entering the respective number: ";
    int input;
    std::cin >> input;
    switch (input) {
        case 1:
        {
            std::cout << "\nPlease enter your name: ";
            std::string name;
            std::cin >> name;
            std::cout << "Please enter the amount of bots you want to play against (1-3): ";
            int bot_amount;
            bool valid_amount_of_bots = false;
            while (!valid_amount_of_bots) {
                std::cin >> bot_amount;
                if (bot_amount > 0 && bot_amount < 4) {
                    valid_amount_of_bots = true;
                }
            }
            Game game = Game(name, bot_amount);
            game.startGame();
            menu = true;
        }
        break;
        case 2:
            show_rules();
            menu = true;
        break;
        case 3:
            menu = false;
        break;
        default:
            menu = true;
            break;
        }
    }
    return 0;
};

