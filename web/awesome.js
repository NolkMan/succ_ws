window.onload = function(){
	var ws = new WebSocket("ws://0.0.0.0:1337")

	ws.onopen = function (ev) {
		console.log("opened")
	}
	ws.onclose = function (ev) {
		console.log("closed")
	}
	ws.onmessage = function (ev) {
		console.log(ev.data + "\n")
	}

	main.onclick = function(){
		ws.send("Twojastara\n")
	}
}
