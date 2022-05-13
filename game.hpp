#pragma once
#include "court.hpp"
#include "entity.hpp"
#include "network.hpp"
#include "player.hpp"
#include "raylib.h"

const int screenWidth = 1280;
const int screenHeight = 720;
const int waOffset = screenWidth / 8 + 80;
const int haOffset = screenHeight / 8 + 80;
const int wmOffset = screenWidth / 8 * 4;
const int hmOffset = screenHeight / 8 * 4;

extern std::vector<Entity *> entities;

void spawnPlayers();
