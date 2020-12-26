const express = require('express');
const app = express();

app.get('/', function(request, response) {
    response.sendFile(path.join(__dirname + '/public/index.html'));
    console.log("Moikka");

});

app.listen(3000, ()=> console.log("Listening port 3000"));

// io.on('connection', function(socket) {
//     socket.on('message', function(message) {
//         io.emit('message', message);
//     });
// });

// setInterval(function(){ 
//     console.log("hi");
//     io.emit('message', 'TEMP');
// }, 5000);