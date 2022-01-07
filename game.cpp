#include "game.hpp"

Game::Game() {
    card_stack = CardStack();
    RealPlayer *real_player = new RealPlayer(0);
    Bot *bot_player = new Bot(1);
    Bot *bot_player2 = new Bot(2);
    Bot *bot_player3 = new Bot(3);
    //Bot *bot_player4 = new Bot(4);
    //Bot *bot_player5 = new Bot(5);
    //Bot *bot_player6 = new Bot(6);
    //Bot *bot_player7 = new Bot(7);
    //Bot *bot_player8 = new Bot(8);
    //Bot *bot_player9 = new Bot(9);
    //Bot *bot_player10 = new Bot(10);
    //Bot *bot_player11 = new Bot(11);
   // Bot *bot_player12 = new Bot(12);
    //Bot *bot_player13 = new Bot(13);

    this->players.push_back(real_player);
    this->players.push_back(bot_player);
    this->players.push_back(bot_player2);
    this->players.push_back(bot_player3);
    //this->players.push_back(bot_player4);
    //this->players.push_back(bot_player5);
    //this->players.push_back(bot_player6);
    //this->players.push_back(bot_player7);
    //this->players.push_back(bot_player8);
    //this->players.push_back(bot_player9);
    //this->players.push_back(bot_player10);
    //this->players.push_back(bot_player11);
    //this->players.push_back(bot_player12);
    //this->players.push_back(bot_player13);


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
            std::cout << "THE STACK IS EMPTY, SHUFFLING" << std::endl;
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
        printTopCard();
        printCardsInHand(); // MUSS SPAETER WEG
        /* sets all playable fields of all the cards player can play to true */
        int num_of_cards_to_play;
        num_of_cards_to_play = this->current_turn.getCurrentPlayer()->possible_cards(top_card, effectNotPending);

        if (num_of_cards_to_play == 0) {
            Effects top_card_effect = top_card.getEffect();
            if(!effectNotPending){
                if(top_card_effect == Effects::draw2 || top_card_effect == Effects::wildDraw4){
                
                if(this->card_stack.getCardsCount() < current_turn.getCardsToAdd()){
                    std::cout << "THE STACK IS EMPTY, SHUFFLING" << std::endl;
                    card_stack = played_cards.copy(played_cards.getPlayedCards());
                }

                this->current_turn.getCurrentPlayer()->draw(this->card_stack, current_turn.getCardsToAdd());
                
                
                std::cout << "You drew: " << current_turn.getCardsToAdd() << " cards" << std::endl;
                printCardsInHand();
                current_turn.setCardsToAdd(0);

                sleep(3);
                nextTurn(no_effect); //change effect to nothing
                continue;
                }
                else if(top_card_effect == Effects::skip){
                    std::cout << "SKIP TURN>>>>>" << std::endl;
                    sleep(3);
                    nextTurn(no_effect); //change effect to nothing
                    continue;
                }
            }
            else{
                /* if the player has no cards to play, draw one */
                this->current_turn.getCurrentPlayer()->draw(this->card_stack, 1);
                std::cout << "You drew a card!" << std::endl;
                printCardsInHand();

                num_of_cards_to_play = this->current_turn.getCurrentPlayer()->possible_cards(top_card, effectNotPending);
                if (num_of_cards_to_play == 0) {
                /* if the player still has no cards to play, next turn begins*/
                sleep(3);
                nextTurn(no_effect);
                continue;
                }
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

        } else {
            /* if it is a bots turn */
            std::cout << "Bots turn" << std::endl;
            sleep(3);
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
        //printCardsInHand(); //FOR TESTING PURPOSES

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
        std::cout << "Choose color:" << std::endl;
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