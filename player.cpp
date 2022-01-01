#include "player.hpp"

Player::Player() {}

RealPlayer::RealPlayer() {
    PlayerCards player_cards = PlayerCards();
    player_value = 1;
}

Bot::Bot() {
    PlayerCards player_cards = PlayerCards();
    player_value = 2;
}

bool Player::play(std::string choice) {
    std::cout << "Mistakes were made" << std::endl;
    return true;
};

bool RealPlayer::play(std::string choice) {
    std::cout << "Hopefully you can read this" << std::endl;
    return true;
}

bool Bot::play(std::string choice) {
    return false;
};

void Player::draw(CardStack &card_stack, int amount) {
    for (int i = 0; i < amount; i++) {
        Card card_to_add = card_stack.pop();
        player_cards.add_card(card_to_add);
    }
}

PlayerCards &Player::getPlayerCards() {
    return player_cards;
}

int &Player::getPlayerValue() {
    return player_value;
}

