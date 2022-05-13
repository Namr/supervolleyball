#pragma once
#include "entity.hpp"
#include <raylib.h>

class Court : public Entity {
public:
  // the higher the number the *less* the padding (fractional)
  const int widthPadding = 8;
  const int lineHeight = 45;
  const int attackLineDist = 10;
  int screenWidth;
  int screenHeight;

  Court(int screenwidth, int screenheight);
  void update();
  void render();
  ~Court();
};
