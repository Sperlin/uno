#include <iostream>
#include "game.hpp"

int main() {
    bool menu = true;
    while (menu) {
        std::cout << "\33[2J";
        std::cout << "Welcome to the main menu!" << std::endl
    << "\t 1) Start a new game!" << std::endl 
    << "\t 2) test" << std::endl
    << "\t 3) Close the application" << std::endl;
    std::cout << "Please select from one of the following by entering the number: ";
    int input;
    std::cin >> input;
    switch (input) {
        case 1:
        {
            std::cout << "\nPlease enter your name: ";
            std::string name;
            std::cin >> name;
            std::cout << "Please enter the amount of bots you want to play against (2-4): ";
            int bot_amount;
            bool valid_amount_of_bots = false;
            while (!valid_amount_of_bots) {
                std::cin >> bot_amount;
                if (bot_amount > 1 && bot_amount < 5) {
                    valid_amount_of_bots = true;
                }
            }
            Game game = Game(name, bot_amount);
            game.startGame();
            menu = true;
        }
        break;
        case 2:
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