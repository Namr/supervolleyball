#pragma once
#include "entity.hpp"
#include "player.hpp"
#include <raylib.h>

class Ball : public Entity {
public:
  Ball();
  void update();
  void render();
  ~Ball();

  // game constants
  const int baseRadius = 30;
  const int returnRadius = 50;
  const int indicatorRadius = 60;
  const int loseThreshold = 2;
  const int timeToTarget = 60;

  int x, y, radius;
  int endX, endY, ownerId;
};

class HostBall : public Ball {
public:
  HostBall();
  void update();
  void render();
  ~HostBall();

private:
  void switchOwners();
  Player *owner;
  int passTime, startX, startY;
};
