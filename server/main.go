package main

import (
  "fmt"
  "log"
  "net/http"
  "github.com/gorilla/websocket"
)

var connections []*websocket.Conn;

// We'll need to define an Upgrader
// this will require a Read and Write buffer size
var upgrader = websocket.Upgrader{
  ReadBufferSize:  1024,
  WriteBufferSize: 1024,
}

func wsEndpoint(w http.ResponseWriter, r *http.Request) {
  //handle a new connection, establish a websocket
  upgrader.CheckOrigin = func(r *http.Request) bool { return true }
  ws, err := upgrader.Upgrade(w, r, nil)
  if err != nil {
    log.Println(err)
  }

  log.Println("New Client Connected")
  connections = append(connections, ws)
  reader(ws)
}

//reads from a websocket connection
func reader(conn *websocket.Conn) {
  for {
    // read in a message
    _, p, err := conn.ReadMessage()
    if err != nil {
      log.Println(err)
      return
    }
    // print out that message for clarity
    fmt.Println(string(p))

    broadcast(string(p))
  }
}


func broadcast(message string) {
  for _, ws := range connections {
    ws.WriteMessage(websocket.TextMessage, []byte(message))
  }
}


func setupRoutes() {
  http.HandleFunc("/ws", wsEndpoint)
}

func main() {
  setupRoutes()
  log.Fatal(http.ListenAndServe(":8080", nil))
}
