#include "game.hpp"

Game::Game() {

}

Game::Game(std::string player_name, int num_of_bots) {
    card_stack = CardStack();
    RealPlayer *real_player = new RealPlayer(0, player_name);
    this->players.push_back(real_player);
    Bot *bot_player1;
    Bot *bot_player2;
    Bot *bot_player3;
    switch(num_of_bots) {
        case 2:
            bot_player1 = new Bot(1, "BOT Alex");
            this->players.push_back(bot_player1);
            break;
        case 3:
            bot_player1 = new Bot(1, "BOT Alex");
            bot_player2 = new Bot(2, "BOT Jeff");
            this->players.push_back(bot_player1);
            this->players.push_back(bot_player2);
            break;
        case 4:
            bot_player1 = new Bot(1, "BOT Alex");
            bot_player2 = new Bot(2, "BOT Jeff");
            bot_player3 = new Bot(3, "BOT Carl");
            this->players.push_back(bot_player1);
            this->players.push_back(bot_player2);
            this->players.push_back(bot_player3);
            break;
        default:
            bot_player1 = new Bot(1, "BOT Alex");
            bot_player2 = new Bot(2, "BOT Jeff");
            bot_player3 = new Bot(3, "BOT Carl");
            this->players.push_back(bot_player1);
            this->players.push_back(bot_player2);
            this->players.push_back(bot_player3);
            break;
    }
    played_cards = PlayedCards();
}

void Game::startGame() {
    /* each player starts with 7 cards */
    for (Player *player : players) {
        player->draw(card_stack, 7);
    }

    /* set first top card (search until you get non effect card)*/
    Card first_card = card_stack.pop();
    while(first_card.getEffect() != Effects::noEffect){
        card_stack.push_back(first_card);
        first_card = card_stack.pop();
    }

    this->played_cards.save(first_card);
    /* set first turn with the real player beginning */
    Turn first_turn = Turn(this->players[0], Effects::noEffect, 0, played_cards.getPlayedCards()[0], "clockwise");
    this->current_turn = first_turn;
    runGame();
}

//wenn moeglich effekte in runGame implementieren
void Game::runGame() {
    bool game_running = true;
    while (game_running) {

        if(card_stack.isEmpty()){
            std::cout << "\n\nTHE STACK IS EMPTY, SHUFFLING" << std::endl;
            card_stack = played_cards.copy(played_cards.getPlayedCards());
        }

        Effects no_effect = Effects::noEffect;
        /* get top card each turn */
        Card top_card = this->current_turn.getTopCard();
        bool effectNotPending = false;
        Effects current_effect = this->current_turn.getEffectFromPreviousPlayer();

        if(current_effect == no_effect || current_effect == Effects::wild || current_effect == Effects::reverse)
        {
            effectNotPending = true;
        }
        printGameTable();
        if (current_effect == Effects::reverse) {
            std::cout << "\n\n\33[2KThe turn order has been reversed!" << std::endl;
            sleep(4);
        }
        printGameTable();
        
        /* sets all playable fields of all the cards player can play to true */
        int num_of_cards_to_play;
        num_of_cards_to_play = this->current_turn.getCurrentPlayer()->possible_cards(top_card, effectNotPending);
        int value_of_current_player = this->current_turn.getCurrentPlayer()->getPlayerValue();

        if (num_of_cards_to_play == 0) {
            Effects top_card_effect = top_card.getEffect();
            if(!effectNotPending){
                if(top_card_effect == Effects::draw2 || top_card_effect == Effects::wildDraw4){
                
                if(this->card_stack.getCardsCount() < current_turn.getCardsToAdd()){
                    std::cout << "\n\nTHE STACK IS EMPTY, SHUFFLING" << std::endl;
                    card_stack = played_cards.copy(played_cards.getPlayedCards());
                }

                this->current_turn.getCurrentPlayer()->draw(this->card_stack, current_turn.getCardsToAdd());
                
                if (value_of_current_player == 0) {
                    std::cout << "\n\nYou have to draw " << current_turn.getCardsToAdd() << " cards!" << std::endl;
                } else {
                    std::cout << "\n\n" << current_turn.getCurrentPlayer()->getPlayerName() << " has to draw " << current_turn.getCardsToAdd() << " cards!" << std::endl;
                }
                sleep(4);
                printGameTable();
                current_turn.setCardsToAdd(0);

                nextTurn(no_effect); //change effect to nothing
                continue;
                }
                else if(top_card_effect == Effects::skip){
                    if (value_of_current_player == 0) {
                        std::cout << "\n\nYour turn gets skipped!" << std::endl;
                    } else {
                        std::cout << "\n\n" << current_turn.getCurrentPlayer()->getPlayerName() << "'s turn gets skipped!" << std::endl;
                    }
                    sleep(4);
                    nextTurn(no_effect); //change effect to nothing
                    continue;
                }
            }
            else{
                /* if the player has no cards to play, draw one */
                this->current_turn.getCurrentPlayer()->draw(this->card_stack, 1);
                if (value_of_current_player == 0) {
                    std::cout << "\n\nYou have to draw a card!" << std::endl;
                } else {
                    std::cout << "\n\n" << current_turn.getCurrentPlayer()->getPlayerName() << " has to draw a card!" << std::endl;
                }
                sleep(4);

                num_of_cards_to_play = this->current_turn.getCurrentPlayer()->possible_cards(top_card, effectNotPending);
                if (num_of_cards_to_play == 0) {
                    /* if the player still has no cards to play, next turn begins*/
                    printGameTable();
                    if (value_of_current_player == 0) {
                        std::cout << "\n\n\33[2KYou have no cards to play!" << std::endl;
                    } else {
                        std::cout << "\n\n\33[2K" << current_turn.getCurrentPlayer()->getPlayerName() << " has no cards to play!" << std::endl;
                    }
                    sleep(4);
                    nextTurn(no_effect);
                    continue;
                } else {
                    printGameTable();
                }
            }
        }

        
        std::string input_from_player;
        Card *card_to_play;
        /* check whether it is the real players turn or a bots turn */
        if (value_of_current_player == 0) {
            /* if it is the real players turn */
            /* get card corresponding to input, loop as long as input is incorrect or does not correspond with a card in hand */
            do {
                printGameTable();
                std::cout << "\n\n\33[2KYour turn: ";
                input_from_player = getInput();
                card_to_play = this->current_turn.getCurrentPlayer()->play(input_from_player, top_card);
            } while (card_to_play == nullptr);

        } else {
            /* if it is a bots turn */
            std::cout << "\n\n\33[2K" << current_turn.getCurrentPlayer()->getPlayerName() << "'s turn!" << std::endl;
            sleep(4);
            /* bot plays first card that it can play */
            card_to_play = this->current_turn.getCurrentPlayer()->play("test", top_card);
        }
        //Choose between different special cards---------------------------------
        if (card_to_play->getColor() == Colors::Black) { 
            Colors colorchoice = colorChoice(value_of_current_player); //Make user or bot choose the color 
            card_to_play->setColor(colorchoice); 
        }
        if(card_to_play->getEffect() == Effects::draw2){
            this->current_turn.addToCardsCounter(2);
        }
        if(card_to_play->getEffect() == Effects::wildDraw4){
            this->current_turn.addToCardsCounter(4);
        }
        if(card_to_play->getEffect() == Effects::reverse){
            this->current_turn.changeDirection(); 
        }

        //------------------------------------------------------------------------
        /* save the card in played_cards and delete it from hand */
        played_cards.save(*card_to_play);
        top_card = played_cards.top();        
        this->current_turn.getCurrentPlayer()->erase_played_card(card_to_play);

        if(this->current_turn.getCurrentPlayer()->getPlayerCards().getCards().size() == 1){
            printUnoPrompt(this->current_turn.getCurrentPlayer()->getPlayerValue()); 
        }

        Effects effect_for_next_turn = top_card.getEffect(); //change

        game_running = nextTurn(effect_for_next_turn);
    }
    /* player has won */
    win(current_turn);
}

bool Game::nextTurn(Effects &effect_for_next_turn) {
    /* check if current player has no cards left and therefore won */
    Player* current_player = this->current_turn.getCurrentPlayer();
    if (current_player->getPlayerCards().getCards().size() == 0) {
        return false;
    } else {
        /* next player, set playable on all cards to false */
        Player* next_player;
        if(this->current_turn.direction == "clockwise"){
            next_player = nextPlayer();
        }
        else{
            next_player = nextPlayerReverse();
        }
        next_player->getPlayerCards().setAllPlayable();
        /* get top card */
        Card top_card = this->played_cards.top();
        Effects effect_from_previous_player = effect_for_next_turn;    

        Turn next_turn = Turn(next_player, effect_from_previous_player, this->current_turn.cards_to_add, top_card, this->current_turn.direction); //pending add cards here
        this->current_turn = next_turn;
        return true;
    }
}

void Game::win(Turn &current_turn) {
    current_turn.setTopCard(played_cards.top());
    Player* winner = current_turn.getCurrentPlayer();
    printGameTable();
    std::cout << "\n\n" << winner->getPlayerName() << " has won the Game!" << std::endl;
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
            std::cout << " " << "\033[1;31m " << card.getValue() << "\033[0m";
            break;

            case Effects::draw2:
            std::cout << " " << "\033[1;31m " << "+2" << "\033[0m";
            break;

            case Effects::reverse:
            std::cout << " " << "\033[1;31m " << "&" << "\033[0m";
            break;

            case Effects::skip:
            std::cout << " " << "\033[1;31m " << "/" << "\033[0m";
            break;

            case Effects::wild:
            std::cout << " " << "\033[1;31m " << "#" << "\033[0m";
            break;

            case Effects::wildDraw4:
            std::cout << " " << "\033[1;31m " << "+4" << "\033[0m";
            break;
        };
        break;

        case Colors::Green:
        switch (card_effect) {
            case Effects::noEffect:
            std::cout << " " << "\033[1;32m " << card.getValue() << "\033[0m";
            break;

            case Effects::draw2:
            std::cout << " " << "\033[1;32m " << "+2" << "\033[0m";
            break;

            case Effects::reverse:
            std::cout << " " << "\033[1;32m " << "&" << "\033[0m";
            break;

            case Effects::skip:
            std::cout << " " << "\033[1;32m " << "/" << "\033[0m";
            break;

            case Effects::wild:
            std::cout << " " << "\033[1;32m " << "#" << "\033[0m";
            break;

            case Effects::wildDraw4:
            std::cout << " " << "\033[1;32m " << "+4" << "\033[0m";
            break;
        };
        break;

        case Colors::Yellow:
        switch (card_effect) {
            case Effects::noEffect:
            std::cout << " " << "\033[1;33m " << card.getValue() << "\033[0m";
            break;

            case Effects::draw2:
            std::cout << " " << "\033[1;33m " << "+2" << "\033[0m";
            break;

            case Effects::reverse:
            std::cout << " " << "\033[1;33m " << "&" << "\033[0m";
            break;

            case Effects::skip:
            std::cout << " " << "\033[1;33m " << "/" << "\033[0m";
            break;

            case Effects::wild:
            std::cout << " " << "\033[1;33m " << "#" << "\033[0m";
            break;

            case Effects::wildDraw4:
            std::cout << " " << "\033[1;33m " << "+4" << "\033[0m";
            break;
        };
        break;

        case Colors::Blue:
        switch (card_effect) {
            case Effects::noEffect:
            std::cout << " " << "\033[1;34m " << card.getValue() << "\033[0m";
            break;

            case Effects::draw2:
            std::cout << " " << "\033[1;34m " << "+2" << "\033[0m";
            break;

            case Effects::reverse:
            std::cout << " " << "\033[1;34m " << "&" << "\033[0m";
            break;

            case Effects::skip:
            std::cout << " " << "\033[1;34m " << "/" << "\033[0m";
            break;

            case Effects::wild:
            std::cout << " " << "\033[1;34m " << "#" << "\033[0m";
            break;

            case Effects::wildDraw4:
            std::cout << " " << "\033[1;34m " << "+4" << "\033[0m";
            break;
        };
        break;

        case Colors::Black:
        switch (card_effect) {
            case Effects::wild:
            std::cout << " " << "\033[1;35m " << "#" << "\033[0m";
            break;

            case Effects::wildDraw4:
            std::cout << " " << "\033[1;35m " << "+4" << "\033[0m";
            break;

        };
        break;
    }
}

void Game::printTopCard() {
    printCard(current_turn.getTopCard());
}

void Game::printCardsInHand() {
    std::vector<Card> cards_of_real_player = players[0]->getPlayerCards().getCards();
    for (Card &card_in_hand : cards_of_real_player) {
        printCard(card_in_hand);
    }
}

void Game::printGameTable() {
    std::cout << "\33[2J";
    int num_of_players = players.size();
    std::string name_of_bot_1 = "";
    std::string name_of_bot_2 = "";
    std::string name_of_bot_3 = "";
    std::string num_of_cards_bot_1 = "";
    std::string num_of_cards_bot_2 = "";
    std::string num_of_cards_bot_3 = "";
    switch(num_of_players) {
      case 2:
        name_of_bot_1 = players[1]->getPlayerName();
        num_of_cards_bot_1 = std::to_string(players[1]->getPlayerCards().getCards().size());
        break;
      case 3:
        name_of_bot_1 = players[1]->getPlayerName();
        num_of_cards_bot_1 = std::to_string(players[1]->getPlayerCards().getCards().size());
        name_of_bot_2 = players[2]->getPlayerName();
        num_of_cards_bot_2 = std::to_string(players[2]->getPlayerCards().getCards().size());
        break;
      case 4:
        name_of_bot_1 = players[1]->getPlayerName();
        num_of_cards_bot_1 = std::to_string(players[1]->getPlayerCards().getCards().size());
        name_of_bot_2 = players[2]->getPlayerName();
        num_of_cards_bot_2 = std::to_string(players[2]->getPlayerCards().getCards().size());
        name_of_bot_3 = players[3]->getPlayerName();
        num_of_cards_bot_3 = std::to_string(players[3]->getPlayerCards().getCards().size());
        break;
    }
    std::string player_name = players[0]->getPlayerName();
    int player_name_length = player_name.length();
    int spaces_to_add_for_name = player_name_length / 2;
    int num_cards_of_real_player = players[0]->getPlayerCards().getCards().size();
    int test = 7 - num_cards_of_real_player;
    int spaces_to_add;
    if (test == 0) {
        spaces_to_add = 0;
    } else if (test > 0) {
        spaces_to_add = (2 * (test - 1) + 1);
    } else if (test < 0) {
        spaces_to_add = (2*test);
    }
    
    /* oberer bot */
    std::cout << "\n" << std::setw(29) << name_of_bot_2 << std::setw(91) << "# During your turn you can input the card you want to play" << std::endl;
    std::cout << std::setw(26) << num_of_cards_bot_2 << std::endl;
    std::cout << std::setw(108) << "# Input format: 'color 0-9|skip|reverse|draw2'";
    std::cout << "\n" << std::setw(127) << "# To play a Wild card or a Draw4 Card, type in 'black wild|draw4'";
    /* linker und rechter bot + oberste karte */
    std::cout << "\n" << std::setw(13) << name_of_bot_1 << std::setw(32) << name_of_bot_3 << std::setw(88) << "# Don't forget to type uno after you have played your second last card!";
    std::cout << "\n" << std::setw(10) << num_of_cards_bot_1 << std::setw(14);
    printTopCard();
    std::cout << std::setw(16) << num_of_cards_bot_3;
    std::cout << "\n" << std::setw(86) << "# Special effect cards: ";
    std::cout << "\n" << std::setw(119) << "# Reverse (&), Skip (/), Draw2 (+2), Draw4 (+4), Wild (#)" << std::endl;
    std::cout << "\n";
    std::cout << std::setw(26+spaces_to_add_for_name) << player_name << std::endl;
    std::cout << std::setw(15+spaces_to_add);
    printCardsInHand();
    std::cout << std::endl;
}

std::string Game::getInput() {
    std::string input_from_player;
    bool correct_input = true;
    bool input_occured = true;
    std::regex pattern_for_choice("((blue|red|yellow|green)\\s{1}([0-9]|draw2|reverse|skip))|black\\s{1}(wild|draw4)");
    do {
        std::getline(std::cin, input_from_player);
        correct_input = std::regex_match(input_from_player, pattern_for_choice);
        if (!input_occured) {
            printGameTable();
            std::cout << "\33[2K\n\nWrong input format (the input should be \"color value/effect\"): ";
        }
        input_occured = false;
    } while (!correct_input);

    return input_from_player;
}

        std::random_device rd;  
        //Standard mersenne_twister_engine seeded with rd()
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());

        int GetRandomNumberBetween(int lower, int upper){
        std::uniform_int_distribution<> dis(lower, upper);
        return dis(gen);
        }

Colors Game::colorChoice(int playerId){
    std::string input_from_player;
    if(playerId == 0){
        printGameTable();
        std::cout << "\33[2K\n\nChoose a color (type in blue or red or yellow or green): ";
        bool correct_input = false;
        std::regex pattern_for_choice("(blue|red|yellow|green)");

        do {
            std::getline(std::cin, input_from_player);
            correct_input = std::regex_match(input_from_player, pattern_for_choice);
        } while (!correct_input);
    
        if(input_from_player == "blue"){
            return Colors::Blue;
        }
        else if(input_from_player == "red"){
            return Colors::Red;
        }
        else if(input_from_player == "yellow"){
            return Colors::Yellow;
        }
        else if(input_from_player == "green"){
            return Colors::Green;
        }

    }
    if(playerId > 0){
        int randomNumber = GetRandomNumberBetween (0, 3); //Random number between 0 and 3
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
    std::cout << input_from_player << std::endl;
    return Colors::Blue; //not possible 
}

void Game::printUnoPrompt(int player_value){
    if(player_value == 0){
        std::string input_from_player;
        bool correct_input = false;
        std::regex pattern_for_choice("(uno|UNO)");
        do {
            std::getline(std::cin, input_from_player);
            correct_input = std::regex_match(input_from_player, pattern_for_choice);
        }
        while(!correct_input);
    }
    std::cout<< "UNO" << std::endl;
}