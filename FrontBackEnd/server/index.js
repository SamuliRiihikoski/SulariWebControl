var app = require('express')();
var server = require('http').Server(app);
var path = require('path');
var io = require('socket.io')(server);
var net = require('net');

server.listen(80);

app.get('/', function(request, response) {
    response.sendFile(path.join(__dirname + '/public/index.html'));
    console.log("Moikka");

});

app.get('/update', function(request, response) {
    console.log("Viesti:" + request.query.sensor);
    let num = parseInt(request.query.sensor);
    num = num / 100;
    let text = num.toString();
    io.emit('sensor', text);
});

app.listen(8080, ()=> {
    console.log("Heisan portista 8080");
});

io.on('connection', function(socket) {
    socket.on('message', function(message) {
        io.emit('message', message);
    });
});

setInterval(function(){ 
    console.log("hi");
    io.emit('message', 'TEMP');
}, 5000);
