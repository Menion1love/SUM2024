import http from "node:http";
import fs from "node:fs/promises";
import process from "node:process";
import express from "express";
import {WebSocketServer} from "ws";

let cnt = 0;

// const requestListener = async (req, res) => {
//   if (req.url == "/") {
//     const contents = await fs.readFile(process.cwd() + "/client/index.html")
//     res.setHeader("Content-Type", "text/html");
//     res.writeHead(200);
//     res.end(contents);
//   } else {
//     if (req.url.endsWith(".js")) {
//       const contents = await fs.readFile(process.cwd() + "/client" + req.url)
//       res.setHeader("Content-Type", "text/javascript");
//       res.writeHead(200);
//       res.end(contents);

//     }
//   }
// };
const app = express();

app.get("/", (req, res, next) => {
  cnt++;
  console.log(cnt);
  next();

})

app.use(express.static("client"))

const server = http.createServer(app);

const wss = new WebSocketServer({ server }); 

wss.on("connection", (ws) => {
  ws.on("message", (message) => {
    console.log(message.toString());
    ws.send(`Hello, ${message}`);
  });

  ws.send("maan");
})

const host = "localhost";
const port = 8000;

server.listen(port, host, () => {
  console.log(`Server started on http://${host}:${port}`);
});


