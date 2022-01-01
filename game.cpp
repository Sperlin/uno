#include "game.hpp"

Game::Game() {
    card_stack = CardStack();
    RealPlayer *real_player = new RealPlayer();
    Bot *bot_player = new Bot();
    this->players.push_back(real_player);
    this->players.push_back(bot_player);
    played_cards = PlayedCards();
}

void Game::startGame() {
    for (Player *player : players) {
        player->draw(card_stack, 7);
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
    int name_of_current_player = this->current_turn.getCurrentPlayer()->getPlayerValue();
    std::string input_from_player;
    if (name_of_current_player == 1) {
        bool inpossible_input = true;
        do {
            input_from_player = getInput();
            inpossible_input = this->current_turn.getCurrentPlayer()->play(input_from_player);
        } while (!inpossible_input);
    } else {
        std::cout << "test";
        //current_turn.getCurrentPlayer().play();
    }
}

void Game::printTopCard() {
    printCard(current_turn.getTopCard());
    std::cout << std::endl;
}

void Game::printCard(Card &card) {
    Colors card_color = card.getColor();
    Effects card_effect = card.getEffect();
    switch(card_color) {
        case Colors::Red:
        switch (card_effect) {
            case Effects::noEffect:
            std::cout << "  " << "\033[1;31m " << card.getValue() << "\033[0m";
            break;

            case Effects::draw2:
            std::cout << "  " << "\033[1;31m " << "+2" << "\033[0m";
            break;

            case Effects::reverse:
            std::cout << "  " << "\033[1;31m " << "&" << "\033[0m";
            break;

            case Effects::skip:
            std::cout << "  " << "\033[1;31m " << "/" << "\033[0m";
            break;
        };
        break;

        case Colors::Green:
        switch (card_effect) {
            case Effects::noEffect:
            std::cout << "  " << "\033[1;32m " << card.getValue() << "\033[0m";
            break;

            case Effects::draw2:
            std::cout << "  " << "\033[1;32m " << "+2" << "\033[0m";
            break;

            case Effects::reverse:
            std::cout << "  " << "\033[1;32m " << "&" << "\033[0m";
            break;

            case Effects::skip:
            std::cout << "  " << "\033[1;32m " << "/" << "\033[0m";
            break;
        };
        break;

        case Colors::Yellow:
        switch (card_effect) {
            case Effects::noEffect:
            std::cout << "  " << "\033[1;33m " << card.getValue() << "\033[0m";
            break;

            case Effects::draw2:
            std::cout << "  " << "\033[1;33m " << "+2" << "\033[0m";
            break;

            case Effects::reverse:
            std::cout << "  " << "\033[1;33m " << "&" << "\033[0m";
            break;

            case Effects::skip:
            std::cout << "  " << "\033[1;33m " << "/" << "\033[0m";
            break;
        };
        break;

        case Colors::Blue:
        switch (card_effect) {
            case Effects::noEffect:
            std::cout << "  " << "\033[1;34m " << card.getValue() << "\033[0m";
            break;

            case Effects::draw2:
            std::cout << "  " << "\033[1;34m " << "+2" << "\033[0m";
            break;

            case Effects::reverse:
            std::cout << "  " << "\033[1;34m " << "&" << "\033[0m";
            break;

            case Effects::skip:
            std::cout << "  " << "\033[1;34m " << "/" << "\033[0m";
            break;
        };
        break;

        case Colors::Black:
        switch (card_effect) {
            case Effects::wild:
            std::cout << "  " << "\033[1;35m " << "#" << "\033[0m";
            break;

            case Effects::wildDraw4:
            std::cout << "  " << "\033[1;35m " << "+4" << "\033[0m";
            break;

        };
        break;
    }
}

void Game::printCardsInHand() {
    std::vector<Card> cards_of_current_player = current_turn.getCurrentPlayer()->getPlayerCards().getCards();
    for (Card &card_in_hand : cards_of_current_player) {
        printCard(card_in_hand);
    }
}

std::string Game::getInput() {
    std::string input_from_player;
    bool correct_input = false;
    std::regex pattern_for_choice("(blue|red|yellow|green|black)\\s{1}([0-9])");
    do {
        std::getline(std::cin, input_from_player);
        correct_input = std::regex_match(input_from_player, pattern_for_choice);
    } while (!correct_input);
    std::cout << "Correct Input!" << std::endl;
    return input_from_player;
}


