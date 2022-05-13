#include "game.hpp"

std::vector<Entity *> entities;

void spawnPlayers() {
  for (int i = 0; i < 2; i++) {
    int wcursed = i == 0 || i == 1 ? 0 : 1;
    int hcursed = i == 0 || i == 2 ? 0 : 1;
    Player *netPlayer;

    if(network::id == i)
      netPlayer = new ControlledPlayer(i, waOffset + wcursed * wmOffset,
                                     haOffset + hcursed * hmOffset, 40);
    else  
      netPlayer = new Player(i, waOffset + wcursed * wmOffset,
                                     haOffset + hcursed * hmOffset, 40);
    entities.push_back(netPlayer);
  }
}

int main(void) {

  ////////////////////////////////////
  // NETWORKING WIP
  //////////////////////////////////////
  if (!emscripten_websocket_is_supported()) {
    return 0;
  }

  network::init_network("ws://127.0.0.1:8080/ws");

  //////////////////////////////////
  // GL Context Init
  //////////////////////////////////

  InitWindow(screenWidth, screenHeight, "supervolleyball");
  SetTargetFPS(60);

  Court court(screenWidth, screenHeight);
  entities.push_back(&court);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BEIGE);
    for (Entity *e : entities) {
      e->update();
      e->render();
    }
    EndDrawing();
  }

  emscripten_websocket_close(network::ws, 1000, "Client Requested to Exit");
  CloseWindow(); // Close window and OpenGL context

  return 0;
}
