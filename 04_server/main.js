import http from "node:http";
import fs from "node:fs"
import fsw from "node:fs/promises"
import express from "express";
import {WebSocketServer} from "ws";

const hist = [];
let cnt = 0
const app = express();

const clients = [];

app.get("/", (req, res, next) => {
  cnt++;
  console.log(cnt);
  console.log(clients)
  next();
})

app.use(express.static("client"))

const server = http.createServer(app);

const wss = new WebSocketServer({ server });   

wss.on("connection", (ws) => {
  clients.push(ws)
  for (let c in clients)
    clients[c].send(hist.join(''))
  ws.on("message", (message) => {
    let newm = message.toString()
    hist.push(newm)
    console.log(hist)
    console.log(hist.join(''))
    fsw.writeFile("./client/chat.txt", hist.join(''))
    for (let c in clients)
      clients[c].send(hist.join(''))
  });

  ws.on("close", () => {
    clients.pop(ws);
  })
})

const host = "localhost";
const port = 8000;

server.listen(port, host, () => {
  hist.push(fs.readFileSync('./client/chat.txt', 'utf8'))
  console.log(`Server started on http://${host}:${port}`);
});
