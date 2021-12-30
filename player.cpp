#include "player.hpp"

Player::Player() {}

RealPlayer::RealPlayer() {
    PlayerCards player_cards = PlayerCards();
}

Bot::Bot() {
    PlayerCards player_cards = PlayerCards();
}

bool Player::play(std::string choice) {
    return true;
};

bool RealPlayer::play(std::string choixe) {
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
