var app = require('express')();
var server = require('http').Server(app);
var path = require('path');
var io = require('socket.io')(server);
var net = require('net');

let index = 0;

server.listen(80);

app.get('/', function(request, response) 
{
    response.sendFile(path.join(__dirname + '/public/index.html'));
    console.log("New connection!");
});

app.get('/update', function(request, response) 
{
    console.log("Viesti:" + request.query.sensor);
    let num = parseInt(request.query.sensor);
    num = num / 100;
    let text = num.toString();
    io.emit('sensor', text);

});

io.on('connection', function(socket) 
{
    socket.on('message', function(message) {
        io.emit('message', message);
        index = 0;
    });
});

setInterval(function() {  // Commands needs to have : in the end. Reason because in arduino that is the mark for end of the command
    
    if (index == 5)
    {
        arduinoReady = false;
        io.emit('message', 'TEMP:');
        index = 0;
    }

    index++;
    
}, 2000);
