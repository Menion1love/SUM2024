import {f} from "./1.js"

console.log("Client js load.")

function initCom() {
  let socket = new WebSocket("ws://localhost:8000")

  socket.onopen = (event) => {
    console.log("Socket open")
    socket.send("les gooo")
  } 

  socket.onmessage = (event) => {
    console.log(`Message ${event.data}`)
  }
}
initCom()
function checkForEnter(e) {
    if (e.keyCode == 13) { 
      document.querySelector(".block .button").click();
    }
  }