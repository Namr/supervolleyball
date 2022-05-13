#include "player.hpp"

Player::Player(int x, int y, int size) {
  this->x = x;
  this->y = y;
  this->radius = size;
}

void Player::update() {}

void Player::render() { DrawCircle(x, y, radius, RED); }

Player::~Player() {}

ControlledPlayer::ControlledPlayer(int x, int y, int size)
    : Player(x, y, size) {}

void ControlledPlayer::update() {
  Player::update();
  if (IsKeyDown(KEY_RIGHT))
    x += 2.0f;
  if (IsKeyDown(KEY_LEFT))
    x -= 2.0f;
  if (IsKeyDown(KEY_UP))
    y -= 2.0f;
  if (IsKeyDown(KEY_DOWN))
    y += 2.0f;
}

void ControlledPlayer::render() { Player::render(); }

ControlledPlayer::~ControlledPlayer() {}

