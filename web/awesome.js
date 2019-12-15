window.onload = function(){
	var ws = new WebSocket("ws://0.0.0.0:1337")

	ws.onopen = function (ev) {
		ws.send("home")
	}
	ws.onclose = function (ev) {
		console.log("closed")
	}
	ws.onmessage = function (ev) {
		page.innerHTML = ev.data;
	}

	main.onclick = function(){
		ws.send("home")
	}
	info.onclick = function(){
		ws.send("info")
	}
	photos.onclick = function(){
		ws.send("photos")
	}
	more.onclick = function(){
		ws.send("more")
	}
}
