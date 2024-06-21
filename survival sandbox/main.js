import http from "node:http";
import express from "express";
import {WebSocketServer} from "ws";

const app = express();

app.use(express.static("client"))

const server = http.createServer(app);

const wss = new WebSocketServer({ server });   

wss.on("connection", (ws) => {
  ws.on("close", () => {
    console.log('bye')
  })
})
const host = "localhost";
const port = 8000;

server.listen(port, host, () => {
  console.log(`Server started on http://${host}:${port}`);
});
