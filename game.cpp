#include "game.hpp"

Game::Game() {
    card_stack = CardStack();
    RealPlayer real_player = RealPlayer();
    Bot bot_player = Bot();
    this->players.push_back(real_player);
    this->players.push_back(bot_player);
    played_cards = PlayedCards();
}

void Game::startGame() {
    for (Player &player : players) {
        player.draw(card_stack, 7);
    }
    Card first_card = card_stack.pop();
    this->played_cards.save(first_card);
    Turn first_turn = Turn(this->players[0], Effects::noEffect, played_cards.getPlayedCards()[0]);
    this->current_turn = first_turn;
    
    // for (Player &player : players) {
    //     player.getPlayerCards().print_cards();
    // }
    // std::cout << current_turn.getTopCard().getId() << std::endl;
    // card_stack.printCards();
    runGame();
}

void Game::runGame() {
    printTopCard();
    printCardsInHand();
    std::string input_from_player;
    input_from_player = getInput();
    this->current_turn.getCurrentPlayer().play(input_from_player);

}

void Game::printTopCard() {
    printCard(current_turn.getTopCard());
    std::cout << std::endl;
}

void Game::printCard(Card &card) {
    if (card.getColor() == Colors::Blue) {
        std::cout << "  " << "\033[1;34m " << card.getValue() << "\033[0m";
    } else if (card.getColor() == Colors::Green) {
        std::cout << "  " << "\033[1;32m " << card.getValue() << "\033[0m";
    } else if (card.getColor() == Colors::Yellow) {
        std::cout << "  " << "\033[1;33m " << card.getValue() << "\033[0m";
    } else if (card.getColor() == Colors::Red) {
        std::cout << "  " << "\033[1;31m " << card.getValue() << "\033[0m";
    } else if (card.getColor() == Colors::Black) {
        std::cout << "  " << "\033[1;35m " << card.getValue() << "\033[0m";
    }
}

void Game::printCardsInHand() {
    std::vector<Card> cards_of_current_player = current_turn.getCurrentPlayer().getPlayerCards().getCards();
    for (Card &card_in_hand : cards_of_current_player) {
        printCard(card_in_hand);
    }
}

std::string Game::getInput() {
    std::string input;
    std::cin >> input;
    return input;
}


