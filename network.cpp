#include "network.hpp"

namespace network {

bool ws_established = false;
EMSCRIPTEN_WEBSOCKET_T ws;
int id = -1;
const std::regex playerPacketRStr("\\dID:(\\d+)X:(\\d+)Y:(\\d+)R:(\\d+)",
                                  std::regex_constants::ECMAScript);
const std::regex
    ballPacketRStr("\\dX:(\\d+)Y:(\\d+)R:(\\d+)O:(\\d+)EX:(\\d+)EY:(\\d+)",
                   std::regex_constants::ECMAScript);
EM_BOOL onopen(int eventType,
               const EmscriptenWebSocketOpenEvent *websocketEvent,
               void *userData) {
  EMSCRIPTEN_RESULT result;
  result = emscripten_websocket_send_utf8_text(websocketEvent->socket,
                                               "SV PLAYER CONNECTED");
  if (result) {
    printf("Failed to emscripten_websocket_send_utf8_text(): %d\n", result);
  }

  ws_established = true;
  ws = websocketEvent->socket;
  return EM_TRUE;
}

EM_BOOL onerror(int eventType,
                const EmscriptenWebSocketErrorEvent *websocketEvent,
                void *userData) {
  puts("Websocket ERROR");
  return EM_TRUE;
}

EM_BOOL onclose(int eventType,
                const EmscriptenWebSocketCloseEvent *websocketEvent,
                void *userData) {
  puts("Websocket Closed");

  return EM_TRUE;
}

EM_BOOL onmessage(int eventType,
                  const EmscriptenWebSocketMessageEvent *websocketEvent,
                  void *userData) {

  if (id == -1 && websocketEvent->isText) {
    id = websocketEvent->data[0] - '0';
    printf("got an ID: %d\n", id);
    spawnPlayers();
    return EM_TRUE;
  }

  if (websocketEvent->isText) {
    // figure out what type of message it is
    int messageType = websocketEvent->data[0] - '0';

    switch (messageType) {
    case PLAYER_MESSAGE: {
      // parse with regex
      std::cmatch cm;
      std::regex_match((char *)websocketEvent->data, cm, playerPacketRStr);
      if (cm.size() != 5)
        printf("weird packet, only had %lu matches: %s\n", cm.size(),
               (char *)websocketEvent->data);
      else {
        // pump into the correct entity (this is a shit method but whatever)
        int pid = stoi(cm[1].str());
        int x = stoi(cm[2].str());
        int y = stoi(cm[3].str());
        int r = stoi(cm[4].str());

        if (pid != id) {
          players[pid]->x = x;
          players[pid]->y = y;
          players[pid]->radius = r;
        }
      }
      break;
    }

    case BALL_MESSAGE: {
      // parse with regex
      std::cmatch cm;
      std::regex_match((char *)websocketEvent->data, cm, ballPacketRStr);
      if (cm.size() != 7)
        printf("weird packet, only had %lu matches: %s\n", cm.size(),
               (char *)websocketEvent->data);
      else {
        // pump into the correct entity (this is a shit method but whatever)
        int x = stoi(cm[1].str());
        int y = stoi(cm[2].str());
        int r = stoi(cm[3].str());
        int o = stoi(cm[4].str());
        int ex = stoi(cm[5].str());
        int ey = stoi(cm[6].str());

        if (id != HOST_ID) {
          ball->x = x;
          ball->y = y;
          ball->radius = r;
          ball->ownerId = o;
          ball->endX = ex;
          ball->endY = ey;
        }
        break;
      }
    }
    }
  }

  return EM_TRUE;
}

void init_network(std::string address) {
  EmscriptenWebSocketCreateAttributes ws_attrs = {address.c_str(), NULL,
                                                  EM_TRUE};
  EMSCRIPTEN_WEBSOCKET_T ws = emscripten_websocket_new(&ws_attrs);
  emscripten_websocket_set_onopen_callback(ws, NULL, onopen);
  emscripten_websocket_set_onerror_callback(ws, NULL, onerror);
  emscripten_websocket_set_onclose_callback(ws, NULL, onclose);
  emscripten_websocket_set_onmessage_callback(ws, NULL, onmessage);
}

EMSCRIPTEN_RESULT sendText(const std::string &message) {
  if (ws_established) {
    EMSCRIPTEN_RESULT result =
        emscripten_websocket_send_utf8_text(ws, message.c_str());

    if (result) {
      printf("sending message failed: %d\n", result);
    }

    return result;
  } else
    return -3;
}
} // namespace network
