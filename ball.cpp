#include "ball.hpp"
#include "game.hpp"
#include "network.hpp"

Ball::Ball() {}
void Ball::update() {}
void Ball::render() {
  DrawCircle(x, y, radius, BLACK);
  DrawCircleLines(endX, endY, returnRadius, BLACK);
  DrawPolyLines({(float)players[ownerId]->x, (float)players[ownerId]->y}, 5,
                indicatorRadius, 0.0f, YELLOW);
}

Ball::~Ball() {}

int lerp(int a, int b, float t) { return a + (int)(b - a) * t; }

void HostBall::switchOwners() {
  startX = owner->x;
  startY = owner->y;

  ownerId = (ownerId + 1) % 4;
  owner = players[ownerId];

  endX = owner->x;
  endY = owner->y;

  passTime = 0;
}

HostBall::HostBall() : Ball() {
  radius = baseRadius;
  ownerId = 0;
  owner = players[ownerId];

  switchOwners();
}

void HostBall::update() {
  passTime++;
  x = lerp(startX, endX, (float)passTime / (float)timeToTarget);
  y = lerp(startY, endY, (float)passTime / (float)timeToTarget);

  if (passTime >= timeToTarget) {
    switchOwners();
  }

  network::sendText(std::to_string(BALL_MESSAGE) + "X:" + std::to_string(x) +
                    "Y:" + std::to_string(y) + "R:" + std::to_string(radius) +
                    "O:" + std::to_string(ownerId) + "EX:" +
                    std::to_string(endX) + "EY:" + std::to_string(endY));
}

void HostBall::render() { Ball::render(); }

HostBall::~HostBall() {}
