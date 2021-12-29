#include <iostream>
#include "game.hpp"

Game::Game() {

}

void Game::startMenu() {
    bool menu = true;
    while (menu) {
        std::cout << "Welcome to the main menu! Please select from one of the following by entering the number" << std::endl 
    << "\t 1) Start a new game!" << std::endl 
    << "\t 2) test" << std::endl
    << "\t 3) Close the application" << std::endl;
    int input;
    std::cin >> input;
    switch (input) {
        case 1:
            startGame();
            menu = false;
        break;
        case 2:
            menu = false;
        break;
        case 3:
            menu = false;
        break;
        default:
            menu = true;
            break;
        }
    }
}

void Game::startGame() {
    CardStack card_stack = CardStack();
    RealPlayer real_player = RealPlayer();
    Bot bot_player = Bot();
    real_player.draw(card_stack, 7);
    bot_player.draw(card_stack, 7);
    card_stack.printCards();
    real_player.getPlayerCards().print_cards();
    bot_player.getPlayerCards().print_cards();
}