#pragma once
#include <emscripten/emscripten.h>
#include <emscripten/websocket.h>
#include <regex>
#include <string>
#include "game.hpp"

namespace network {

struct playerPacket {
  int x, y, r;
};

extern int id;
extern const std::regex packetRStr;
extern bool ws_established;
extern EMSCRIPTEN_WEBSOCKET_T ws;

extern struct playerPacket playerPackets[2];

EM_BOOL onopen(int eventType,
               const EmscriptenWebSocketOpenEvent *websocketEvent,
               void *userData);

EM_BOOL onerror(int eventType,
                const EmscriptenWebSocketErrorEvent *websocketEvent,
                void *userData);

EM_BOOL onclose(int eventType,
                const EmscriptenWebSocketCloseEvent *websocketEvent,
                void *userData);

EM_BOOL onmessage(int eventType,
                  const EmscriptenWebSocketMessageEvent *websocketEvent,
                  void *userData);

void init_network(std::string address);

EMSCRIPTEN_RESULT sendText(const std::string &message);

} // namespace network
