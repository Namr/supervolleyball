#pragma once
#include <vector>

class Entity {
public:
  virtual void update() = 0;
  virtual void render() = 0;
};
