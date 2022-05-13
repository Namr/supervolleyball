#include "player.hpp"

Player::Player(int id, int x, int y, int size) {
  this->x = x;
  this->y = y;
  this->radius = size;
  this->id = id;
}

void Player::update() {
  this->x = network::playerPackets[id].x;
  this->y = network::playerPackets[id].y;
  this->radius = network::playerPackets[id].r;
}

void Player::render() { DrawCircle(x, y, radius, RED); }

Player::~Player() {}

ControlledPlayer::ControlledPlayer(int id, int x, int y, int size)
    : Player(id, x, y, size) {}

void ControlledPlayer::update() {
  if (IsKeyDown(KEY_D))
    x += 2.0f;
  if (IsKeyDown(KEY_A))
    x -= 2.0f;
  if (IsKeyDown(KEY_W))
    y -= 2.0f;
  if (IsKeyDown(KEY_S))
    y += 2.0f;
  
  network::sendText("ID:" + std::to_string(network::id) + "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "R:" + std::to_string(radius));
}

void ControlledPlayer::render() { Player::render(); }

ControlledPlayer::~ControlledPlayer() {}
