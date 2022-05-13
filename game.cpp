#include "raylib.h"
#include "entity.hpp"
#include "court.hpp"
#include "player.hpp"

int main(void) {
  const int screenWidth = 1280;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "supervolleyball");
  SetTargetFPS(60);

  std::vector<Entity*> entities;
  Court court(screenWidth, screenHeight);
  ControlledPlayer player(200, 200, 40);
  
  entities.push_back(&court);
  entities.push_back(&player);

  // Main game loop
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BEIGE);
    for(Entity* e : entities) {
      e->update();
      e->render();
    }
    EndDrawing();
  }

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
