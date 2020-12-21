var app = require('express')();
var server = require('http').Server(app);
var path = require('path');
var io = require('socket.io')(server);

server.listen(3000);

app.get('/', function(request, response) {
    response.sendFile(path.join(__dirname + '/public/index.html'));
});

io.on('connection', function(socket) {
    socket.on('message', function(message) {
        io.emit('message', message);
    });
});
