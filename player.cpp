#include "player.hpp"

/* split string helper function */
void split(const std::string& s, char c, std::vector<std::string>& v) {
    std::string::size_type i = 0;
    std::string::size_type j = s.find(c);

    while (j != std::string::npos) {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);

        if (j == std::string::npos) {
            v.push_back(s.substr(i, s.length()));
        }
    }
}

Player::Player() {}

Player::Player(int value) {}

RealPlayer::RealPlayer(int value) {
    PlayerCards player_cards = PlayerCards();
    player_value = value;
}

Bot::Bot(int value) {
    PlayerCards player_cards = PlayerCards();
    player_value = value;
}

PlayerCards &Player::getPlayerCards() {
    return player_cards;
}

int &Player::getPlayerValue() {
    return player_value;
}

Card *Player::play(std::string choice, Card &top_card) {
    std::cout << "Mistakes were made" << std::endl;
    return nullptr;
};

Card *RealPlayer::play(std::string choice, Card &top_card) {
    /* return and "play" chosen card */
    //std::cout << "Hopefully you can read this" << std::endl;
    std::vector<std::string> input_elements;
    /* split input in color and value */
    split(choice, ' ', input_elements);
    Colors color_of_input_card = getColorOfInputCard(input_elements[0]);
    int value_of_input_card = getValueOfInputCard(input_elements[1]);
    /* check if chosen card is actually in hand and playable */
    Card *played_card = nullptr;
    for (Card &card : this->player_cards.getCards()) {
        if (color_of_input_card == card.getColor() && value_of_input_card == card.getValue()) {
            //std::cout << card.getPlayable() << std::endl; // FOR TESTING PURPOSES
            if (card.getPlayable()) {
                played_card = &card;
                //std::cout << played_card->getValue() << std::endl; // FOR TESTING PURPOSES
                //std::cout << "test";
                break;
            }
        }
    }
    return played_card;
}

Card *Bot::play(std::string choice, Card &top_card) {
    /* return and "play" first playable card */
    //possible_cards(top_card);
    Card *played_card = nullptr;
    for (Card &card : this->player_cards.getCards()) {
        //std::cout << card.getPlayable() << std::endl;
        if (card.getPlayable()) {
            played_card = &card;
            //std::cout << played_card->getValue() << std::endl;
            //std::cout << "test";
            break;
        }
    }
    return played_card;
};


int Player::possible_cards(Card &top_card, bool cardPlayed) {
    /* set playable to true on all playable card */
    int num_of_playable_cards = 0;
    for (Card &card : player_cards.getCards()) {

        Colors color_card_hand = card.getColor();
        int value_card_hand = card.getValue();
        Colors color_top_card = top_card.getColor();
        int value_top_card = top_card.getValue();
        Effects effect_card_hand = card.getEffect();
        Effects effect_top_card = top_card.getEffect();
        
        if(effect_top_card == Effects::wildDraw4 && effect_card_hand == Effects::draw2 || effect_top_card == Effects::draw2 && effect_card_hand == Effects::wildDraw4){
            card.setPlayable(true);
            num_of_playable_cards++;
        }

        if(effect_top_card == Effects::noEffect || effect_card_hand == effect_top_card || cardPlayed){
            if (color_card_hand == Colors::Black || color_card_hand == color_top_card || value_card_hand == value_top_card) {
                card.setPlayable(true);
                num_of_playable_cards++;
            }
        }
    }
    return num_of_playable_cards;
}

void Player::draw(CardStack &card_stack, int amount) {
    for (int i = 0; i < amount; i++) {
        Card card_to_add = card_stack.pop();
        player_cards.add_card(card_to_add);
    }
}

void Player::erase_played_card(Card *card_to_erase) {
    Colors color_of_card_to_erase = card_to_erase->getColor();
    int value_of_card_to_erase = card_to_erase->getValue();
    int index_of_card = 0;
    for (Card &card : this->player_cards.getCards()) {
        if (color_of_card_to_erase == card.getColor() && value_of_card_to_erase == card.getValue()) {
            this->player_cards.getCards().erase(this->player_cards.getCards().begin() + index_of_card);
            break;
        }
        index_of_card++;
    }
}

Colors Player::getColorOfInputCard(std::string color_string) {
    if (color_string == "red") {
        return Colors::Red;
    } else if (color_string == "green") {
        return Colors::Green;
    } else if (color_string == "yellow") {
        return Colors::Yellow;
    } else if (color_string == "blue") {
        return Colors::Blue;
    } else if (color_string == "black") {
        return Colors::Black;
    } else {
        return Colors::Black;
    }
}

int Player::getValueOfInputCard(std::string value_string) {
    if (value_string == "draw2") {
        return 10;
    } else if (value_string == "reverse") {
        return 11;
    } else if (value_string == "skip") {
        return 12;
    } else if (value_string == "draw4") {
        return 13;
    } else if (value_string == "wild") {
        return 14;
    } else {
        return std::stoi(value_string);
    }
}
