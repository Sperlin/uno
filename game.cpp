#include "game.hpp"

Game::Game() {
    card_stack = CardStack();
    RealPlayer *real_player = new RealPlayer(0);
    Bot *bot_player = new Bot(1);
    Bot *bot_player2 = new Bot(2);
    this->players.push_back(real_player);
    this->players.push_back(bot_player);
    this->players.push_back(bot_player2);
    played_cards = PlayedCards();
}

void Game::startGame() {
    /* each player starts with 7 cards */
    for (Player *player : players) {
        player->draw(card_stack, 7);
    }

    /* set first top card (ANPASSEN, DASS KEINE EFFEKT KARTEN ALS ERSTES LIEGEN */
    Card first_card = card_stack.pop();
    while(first_card.getEffect() != Effects::noEffect){
        card_stack.getCards().push_back(first_card); 
        first_card = card_stack.pop();
    }

    this->played_cards.save(first_card);
    /* set first turn with the real player beginning */
    Turn first_turn = Turn(this->players[0], Effects::noEffect, played_cards.getPlayedCards()[0], "clockwise");
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
        /* get top card each turn */
        Card top_card = this->current_turn.getTopCard();
        printTopCard();
        printCardsInHand(); // MUSS SPAETER WEG
        /* sets all playable fields of all the cards player can play to true */
        int num_of_cards_to_play;
        num_of_cards_to_play = this->current_turn.getCurrentPlayer()->possible_cards(top_card);
        played_effect = current_turn.getEffectFromPreviousPlayer();

        //if(current_turn.getEffectFromPreviousPlayer() == Effects::draw2){
//
  //      }

        //If the player has no other skip turn card, skip to the next player
        if(played_effect == Effects::skip){ // (&& num_of_cards_to_play == 0) PROBLEMATISCH, weil karten mit der selben farbe OHNE die value mitgezaehlt werden
            Effects noEffect = Effects::noEffect;
            nextTurn(noEffect);
            continue; //Skip to the next turn
        }

        if (num_of_cards_to_play == 0) {
            /* if the player has no cards to play, draw one */
            this->current_turn.getCurrentPlayer()->draw(this->card_stack, 1);
            std::cout << "You drew a card!" << std::endl;
            printCardsInHand();
            num_of_cards_to_play = this->current_turn.getCurrentPlayer()->possible_cards(top_card);
            /* if the player still has no cards to play, next turn begins*/
            if (num_of_cards_to_play == 0) {
                sleep(3);
                Effects no_effect = Effects::noEffect;
                nextTurn(no_effect);
                continue;
            }
        }
        int value_of_current_player = this->current_turn.getCurrentPlayer()->getPlayerValue();
        std::string input_from_player;
        Card *card_to_play;
        /* check whether it is the real players turn or a bots turn */
        if (value_of_current_player == 0) {
            /* if it is the real players turn */
            //printCardsInHand(); //MUSS SPAETER HIERHIN, damit Karten von Bots nicht mehr gezeigt werden
            /* get card corresponding to input, loop as long as input is incorrect or does not correspond with a card in hand */
            do {
                input_from_player = getInput();
                card_to_play = this->current_turn.getCurrentPlayer()->play(input_from_player, top_card);
            } while (card_to_play == nullptr);
            // if (card_to_play->getColor() == Colors::Black) { //FOR TESTING PURPOSES: damit das spiel beendet werden kann wenn eine wild karte gelegt wird
            //     card_to_play->setColor(Colors::Blue);
            // }
        } else {
            /* if it is a bots turn */
            std::cout << "Bots turn" << std::endl;
            sleep(3);
            /* bot plays first card that it can play */
            card_to_play = this->current_turn.getCurrentPlayer()->play("test", top_card);
            // if (card_to_play->getColor() == Colors::Black) { //FOR TESTING PURPOSES: damit das spiel beendet werden kann wenn eine wild karte gelegt wird
            //     card_to_play->setColor(Colors::Blue);
            // }
            //game_running = false; //FOR TESTING PURPOSES
        }
        /* save the card in played_cards and delete it from hand */
        played_cards.save(*card_to_play);
        this->current_turn.getCurrentPlayer()->erase_played_card(card_to_play);
        printCardsInHand(); //FOR TESTING PURPOSES
        /* get effect of the played card for the next turn and begin next turn */
        top_card = played_cards.top();
        //Change direction here ----------------------------------------
        if(top_card.getEffect() == Effects::reverse){
            this->current_turn.changeDirection();
        }
        else if(played_cards.top().getEffect() == Effects::wild){
            Colors chosen_color = colorChoice(value_of_current_player); //Make user or bot choose the color
            played_cards.top().setColor(chosen_color);  
        }
        Effects effect_for_next_turn = top_card.getEffect(); //change
        game_running = nextTurn(effect_for_next_turn);
    }
    /* player has won */
    win(current_turn);
}

bool Game::nextTurn(Effects &played_effect) {
    /* check if current player has no cards left and therefore won */
    Player* current_player = this->current_turn.getCurrentPlayer();
    if (current_player->getPlayerCards().getCards().size() == 0) {
        return false;
    } else {
        /* next player, set playable on all cards to false */
        Player* next_player;
        if(this->current_turn.getDirection() == "clockwise"){
            next_player = nextPlayer();
        }
        else{
            next_player = nextPlayerReverse();
        }
        next_player->getPlayerCards().setAllPlayable();
        /* get top card */
        Card top_card = this->played_cards.top();
        /* get played effect */
        Effects effect_for_next_turn = played_effect;
        /* create and set new Turn */
        Turn next_turn = Turn(next_player, effect_for_next_turn, top_card, this -> current_turn.getDirection());
        this->current_turn = next_turn;
        return true;
    }
}

void Game::win(Turn &current_turn) {
    Player* winner = current_turn.getCurrentPlayer();
    std::cout << "Player " << winner->getPlayerValue() << " has won the Game!" << std::endl;
}

Player* Game::nextPlayer() {
    /* get next player for next turn */
    int num_of_players = players.size();
    int current_player_value = this->current_turn.getCurrentPlayer()->getPlayerValue();
    if (current_player_value == num_of_players - 1) {
        return players[0];
    } else {
        return players[current_player_value + 1];
    }
}

Player* Game::nextPlayerReverse() {
    /* get next player for next turn, if reverse effect is on */
    int num_of_players = players.size();
    int current_player_value = this->current_turn.getCurrentPlayer()->getPlayerValue();
    if (current_player_value == 0) {
        return players[num_of_players - 1];
    } else {
        return players[current_player_value - 1];
    }
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

void Game::printTopCard() {
    std::cout << "\n\nCurrent Top Card: ";
    printCard(current_turn.getTopCard());
    std::cout << std::endl;
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
Colors Game::colorChoice(int playerId){
    if(playerId == 0){
        // for real player
        std::string input_from_player;
        bool correct_input = false;
        std::regex pattern_for_choice("(blue|red|yellow|green)");
    do {
        std::getline(std::cin, input_from_player);
        correct_input = std::regex_match(input_from_player, pattern_for_choice);
    } while (!correct_input);
        if (input_from_player == "blue") {
            return Colors::Blue;
        } else if (input_from_player == "red") {
            return Colors::Red;
        } else if (input_from_player == "yellow") {
            return Colors::Yellow;
        } else if (input_from_player == "green") {
            return Colors::Green;
        }
        // switch(input_from_player){
        //     case "blue":
        //         return Colors::Blue;
        //     case "red":
        //         return Colors::Red;
        //     case "yellow":
        //         return Colors::Yellow;
        //     case "green":
        //         return Colors::Green;
        // }
    }
    if(playerId > 0){
        //Random number between 0 and 3, for bots
        int randomNumber = rand() % 4; 
        switch(randomNumber){
            case 0:
                return Colors::Blue;
            case 1:
                return Colors::Red;
            case 2:
                return Colors::Yellow;
            case 3:
                return Colors::Green;
        }
    }

}

