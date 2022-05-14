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

  int x, y, radius;
};

class HostBall : public Entity {
public:
  HostBall();
  void update();
  void render();
  ~HostBall();

  int x, y, radius;
  const int baseRadius = 30;
  const float p = 0.2f;
  const int loseThreshold = 2;
  const int timeToTarget = 60;

private:
  void switchOwners();
  Player *owner;
  int ownerId;
  int passTime;
  int startX, startY, endX, endY;
};
