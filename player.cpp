#include "player.hpp"

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

Card *Player::play(std::string choice, Card &top_card) {
    std::cout << "Mistakes were made" << std::endl;
    return nullptr;
};

Card *RealPlayer::play(std::string choice, Card &top_card) {
    //std::cout << "Hopefully you can read this" << std::endl;
    std::vector<std::string> input_elements;
    split(choice, ' ', input_elements);
    possible_cards(top_card);
    Colors color_of_input_card = getColorOfInputCard(input_elements[0]);
    int value_of_input_card = getValueOfInputCard(input_elements[1]);
    int index_of_card = 0;
    Card *played_card = nullptr;
    for (Card &card : this->player_cards.getCards()) {
        if (color_of_input_card == card.getColor() && value_of_input_card == card.getValue()) {
            //std::cout << card.getPlayable() << std::endl;
            if (card.getPlayable()) {
                played_card = &card;
                //std::cout << played_card->getValue() << std::endl;
                //std::cout << "test";
                break;
            }
        }
        index_of_card++;
    }
    return played_card;
}

Card *Bot::play(std::string choice, Card &top_card) {
    possible_cards(top_card);
    int index_of_card = 0;
    Card *played_card = nullptr;
    for (Card &card : this->player_cards.getCards()) {
        //std::cout << card.getPlayable() << std::endl;
        if (card.getPlayable()) {
            played_card = &card;
            //std::cout << played_card->getValue() << std::endl;
            //std::cout << "test";
            break;
        }
        index_of_card++;
    }
    return played_card;
};

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
            //std::cout << card.getPlayable() << std::endl;
            this->player_cards.getCards().erase(this->player_cards.getCards().begin() + index_of_card);
            break;
        }
        index_of_card++;
    }
}

PlayerCards &Player::getPlayerCards() {
    return player_cards;
}

int &Player::getPlayerValue() {
    return player_value;
}

void Player::possible_cards(Card &top_card) {
    for (Card &card : player_cards.getCards()) {
        Colors color_card_hand = card.getColor();
        int value_card_hand = card.getValue();
        Colors color_top_card = top_card.getColor();
        int value_top_card = top_card.getValue();
        if (color_card_hand == Colors::Black || color_card_hand == color_top_card || value_card_hand == value_top_card) {
            card.setPlayable(true);
            //std::cout << "Possible: " << card.getValue() << card.getPlayable() << std::endl;
        }
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
