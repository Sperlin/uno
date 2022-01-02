#include "game.hpp"

Game::Game() {
    card_stack = CardStack();
    RealPlayer *real_player = new RealPlayer(0);
    Bot *bot_player = new Bot(1);
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

//wenn moeglich effekte in runGame implementieren
void Game::runGame() {
    bool game_running = true;
    while (game_running) {
        printTopCard();
        printCardsInHand();
        Card top_card = this->current_turn.getTopCard();
        int num_of_cards_to_play;
        num_of_cards_to_play = this->current_turn.getCurrentPlayer()->possible_cards(top_card);
        if (num_of_cards_to_play == 0) {
            this->current_turn.getCurrentPlayer()->draw(this->card_stack, 1);
            std::cout << "You drew a card!" << std::endl;
            printCardsInHand();
            num_of_cards_to_play = this->current_turn.getCurrentPlayer()->possible_cards(top_card);
            if (num_of_cards_to_play == 0) {
                Effects no_effect = Effects::noEffect;
                nextTurn(no_effect);
                continue;
            }
        }
        int value_of_current_player = this->current_turn.getCurrentPlayer()->getPlayerValue();
        std::string input_from_player;
        Card *card_to_play;
        if (value_of_current_player == 0) {
            //printCardsInHand(); //MUSS SPAETER HIERHIN
            do {
                input_from_player = getInput();
                card_to_play = this->current_turn.getCurrentPlayer()->play(input_from_player, top_card);
            } while (card_to_play == nullptr);
            if (card_to_play->getColor() == Colors::Black) { //FOR TESTING PURPOSES: damit das spiel beendet werden kann wenn eine wild karte gelegt wird
                card_to_play->setColor(Colors::Blue);
            }
            played_cards.save(*card_to_play);
            top_card = played_cards.top();
            this->current_turn.getCurrentPlayer()->erase_played_card(card_to_play);
            printCardsInHand(); //FOR TESTING PURPOSES
        } else {
            std::cout << "Bots turn" << std::endl;
            sleep(3);
            card_to_play = this->current_turn.getCurrentPlayer()->play("test", top_card);
            if (card_to_play->getColor() == Colors::Black) { //FOR TESTING PURPOSES: damit das spiel beendet werden kann wenn eine wild karte gelegt wird
                card_to_play->setColor(Colors::Blue);
            }
            played_cards.save(*card_to_play);
            top_card = played_cards.top();
            this->current_turn.getCurrentPlayer()->erase_played_card(card_to_play);
            //game_running = false; //FOR TESTING PURPOSES
            printCardsInHand(); //FOR TESTING PURPOSES
        }
        Effects effect_for_next_turn = top_card.getEffect();
        game_running = nextTurn(effect_for_next_turn);
    }
    win(current_turn);
}

bool Game::nextTurn(Effects &played_effect) {
    //check if current player has won
    Player* current_player = this->current_turn.getCurrentPlayer();
    if (current_player->getPlayerCards().getCards().size() == 0) {
        return false;
    } else {
        //next player, set playable on all cards false
        Player* next_player = nextPlayer();
        next_player->getPlayerCards().setAllPlayable();
        //get top card
        Card top_card = this->played_cards.top();
        //get played effect
        Effects effect_for_next_turn = played_effect;
        //create and set new Turn
        Turn next_turn = Turn(next_player, effect_for_next_turn, top_card);
        this->current_turn = next_turn;
        return true;
    }
}

Player* Game::nextPlayer() {
    int num_of_players = players.size();
    int current_player_value = this->current_turn.getCurrentPlayer()->getPlayerValue();
    if (current_player_value == num_of_players - 1) {
        return players[0];
    } else {
        return players[current_player_value + 1];
    }
}

Player* Game::nextPlayerReverse() {
    int num_of_players = players.size();
    int current_player_value = this->current_turn.getCurrentPlayer()->getPlayerValue();
    if (current_player_value == 0) {
        return players[num_of_players - 1];
    } else {
        return players[current_player_value - 1];
    }
}

void Game::win(Turn &current_turn) {
    Player* winner = current_turn.getCurrentPlayer();
    std::cout << "Player " << winner->getPlayerValue() << " has won the Game!" << std::endl;
}

void Game::printTopCard() {
    std::cout << "\n\nCurrent Top Card: ";
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

            case Effects::wild:
            std::cout << "  " << "\033[1;31m " << "#" << "\033[0m";
            break;

            case Effects::wildDraw4:
            std::cout << "  " << "\033[1;31m " << "+4" << "\033[0m";
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

            case Effects::wild:
            std::cout << "  " << "\033[1;32m " << "#" << "\033[0m";
            break;

            case Effects::wildDraw4:
            std::cout << "  " << "\033[1;32m " << "+4" << "\033[0m";
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

            case Effects::wild:
            std::cout << "  " << "\033[1;33m " << "#" << "\033[0m";
            break;

            case Effects::wildDraw4:
            std::cout << "  " << "\033[1;33m " << "+4" << "\033[0m";
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

            case Effects::wild:
            std::cout << "  " << "\033[1;34m " << "#" << "\033[0m";
            break;

            case Effects::wildDraw4:
            std::cout << "  " << "\033[1;34m " << "+4" << "\033[0m";
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
    std::cout << "Cards of Player " << current_turn.getCurrentPlayer()->getPlayerValue() << ":";
    for (Card &card_in_hand : cards_of_current_player) {
        printCard(card_in_hand);
    }
    std::cout << std::endl;
}

std::string Game::getInput() {
    std::string input_from_player;
    bool correct_input = false;
    std::regex pattern_for_choice("((blue|red|yellow|green)\\s{1}([0-9]|draw2|reverse|skip))|black\\s{1}(wild|draw4)");
    do {
        std::getline(std::cin, input_from_player);
        correct_input = std::regex_match(input_from_player, pattern_for_choice);
    } while (!correct_input);
    //std::cout << "Correct Input!" << std::endl;
    return input_from_player;
}


