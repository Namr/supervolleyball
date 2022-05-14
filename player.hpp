#pragma once
#include <string>
#include <raylib.h>
#include "entity.hpp"

class Player : public Entity {
public:
  int x, y, radius, id;
  Player(int id, int x, int y, int size);
  void update();
  void render();
  ~Player();
};

class ControlledPlayer : public Player {
public:
  ControlledPlayer(int id, int x, int y, int size);
  void update();
  void render();
  ~ControlledPlayer();
};

