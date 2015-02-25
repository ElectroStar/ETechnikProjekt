//============================================================================
// Datei	: player.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::stop() {
    stopStream = true;
}

bool Player::isStopped() const {
    return this->stopStream;
}
