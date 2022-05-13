#pragma once
#include "entity.hpp"
#include <raylib.h>

class Player : public Entity {
public:
  int x, y, radius;
  Player(int x, int y, int size);
  void update();
  void render();
  ~Player();
};

class ControlledPlayer : public Player {
public:
  ControlledPlayer(int x, int y, int size);
  void update();
  void render();
  ~ControlledPlayer();
};
