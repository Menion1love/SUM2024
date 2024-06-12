let usName = "";
let html = '<table id="mytable" class="mytable"><tbody><td class="mytd">'

let socket = new WebSocket("ws://localhost:8000")
  
socket.onopen = (event) => {
  document.getElementById('msg_table').innerHTML = html + event.data + '</td></tbody></table>';
} 
socket.onmessage = (event) => {
  document.getElementById('msg_table').innerHTML = html + event.data + '</td></tbody></table>';
} 

document.getElementById("name").addEventListener("keydown", function(e) {
  if (e.which === 13 || e.which === 9)
  {
    let v = document.getElementById("name").value;
    if (v != "" && v.indexOf(' ') == -1)
      usName = v
  }
})
  
document.getElementById("message").addEventListener("keydown", function(e) {
  if (e.which === 13)
  {
    let v = document.getElementById("message").value
    if (v != "" && usName != "")
      {
        let m = '<br>' + `${usName}: ${v}` + '<br/>'
        document.getElementById("message").value = ""
        socket.send(m.toString())
    } 
  } 
})
