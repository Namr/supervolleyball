#include "game.hpp"

std::vector<Entity *> entities;
Player *players[4];
Ball *ball;

// the main loop doesn't (and can't) know when we have actually connected to the
// websocket so a socket callback has to call this function in order to actually
// spawn the players once we are connected
void spawnPlayers() {
  for (int i = 0; i < 4; i++) {
    int wcursed = i == 0 || i == 1 ? 0 : 1;
    int hcursed = i == 0 || i == 2 ? 0 : 1;
    Player *netPlayer;

    if (network::id == i)
      netPlayer = new ControlledPlayer(i, waOffset + wcursed * wmOffset,
                                       haOffset + hcursed * hmOffset, 40);
    else
      netPlayer = new Player(i, waOffset + wcursed * wmOffset,
                             haOffset + hcursed * hmOffset, 40);
    entities.push_back(netPlayer);
    players[i] = netPlayer;
  }

  // host manages state of the game(ball), rest just get info over the network
  // and render
  if (network::id == HOST_ID) {
    HostBall *hball = new HostBall();
    entities.push_back(hball);
  } else {
    ball = new Ball();
    entities.push_back(ball);
  }
}

int main(void) {
  // need websockets for this game to work
  // init them here
  if (!emscripten_websocket_is_supported()) {
    return 0;
  }
  network::init_network("ws://127.0.0.1:8080/ws");

  //////////////////////////////////
  // GL Context Init
  //////////////////////////////////

  InitWindow(screenWidth, screenHeight, "supervolleyball");
  SetTargetFPS(60);

  // create the background
  Court court(screenWidth, screenHeight);
  entities.push_back(&court);

  // game loop, all entities updated and rendered
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BEIGE);
    for (Entity *e : entities) {
      e->update();
      e->render();
    }
    EndDrawing();
  }

  // clean up and exit
  emscripten_websocket_close(network::ws, 1000, "Client Requested to Exit");
  CloseWindow(); // Close window and OpenGL context

  return 0;
}
