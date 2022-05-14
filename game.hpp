#pragma once
#include "raylib.h"
#include "network.hpp"
#include "entity.hpp"
#include "court.hpp"
#include "player.hpp"
#include "ball.hpp"

#define HOST_ID 0

const int screenWidth = 1280;
const int screenHeight = 720;
const int waOffset = screenWidth / 8 + 80;
const int haOffset = screenHeight / 8 + 80;
const int wmOffset = screenWidth / 8 * 4;
const int hmOffset = screenHeight / 8 * 4;

extern std::vector<Entity *> entities;
extern Player* players[4];
extern Ball* ball;

void spawnPlayers();
