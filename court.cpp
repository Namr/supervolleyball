#include "court.hpp"

Court::Court(int screenwidth, int screenheight) {
  this->screenWidth = screenwidth;
  this->screenHeight = screenheight;
}

void Court::update() {}

void Court::render() {
  // court outline
  DrawRectangle(screenWidth / widthPadding, screenHeight / widthPadding,
                screenWidth - 2 * (screenWidth / widthPadding),
                screenHeight / lineHeight, WHITE);
  DrawRectangle(screenWidth / widthPadding,
                screenHeight - (screenHeight / widthPadding),
                screenWidth - 2 * (screenWidth / widthPadding),
                screenHeight / lineHeight, WHITE);

  DrawRectangle(screenWidth / widthPadding, screenHeight / widthPadding,
                screenHeight / lineHeight,
                screenHeight - 2 * (screenHeight / widthPadding), WHITE);
  DrawRectangle(screenWidth - (screenWidth / widthPadding),
                screenHeight / widthPadding, screenHeight / lineHeight,
                screenHeight - 2 * (screenHeight / widthPadding), WHITE);
  // game lines
  DrawRectangle(screenWidth / 2,
                (screenHeight / widthPadding) - (screenHeight / lineHeight),
                screenHeight / lineHeight,
                screenHeight - 2 * (screenHeight / widthPadding) +
                    3 * (screenHeight / lineHeight),
                WHITE);

  DrawRectangle(screenWidth / 2 + (screenWidth / attackLineDist),
                screenHeight / widthPadding, screenHeight / lineHeight,
                screenHeight - 2 * (screenHeight / widthPadding), WHITE);
  DrawRectangle(screenWidth / 2 - (screenWidth / attackLineDist),
                screenHeight / widthPadding, screenHeight / lineHeight,
                screenHeight - 2 * (screenHeight / widthPadding), WHITE);
}

Court::~Court() {}
