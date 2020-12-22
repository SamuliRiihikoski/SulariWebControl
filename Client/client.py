import socketio
import socket

TCP_IP = '192.168.1.72'
TCP_PORT = 80
BUFFER_SIZE = 1024

sio = socketio.Client()

@sio.event
def connect():
    print('Connection established')

@sio.event
def my_message(data):
    print('message received with ', data)
    sio.emit('my response', {'responce': 'my response'})

@sio.event
def disconnect():
    print('disconnected from server')

@sio.on('message')
def print_message(message):
    print('message: ' + message)

    MESSAGE = ''
    MESSAGE = message
    MESSAGE = MESSAGE.encode('utf-8')
    

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((TCP_IP, TCP_PORT))
    s.send(MESSAGE)
    s.close()


sio.connect('http://3.140.78.112:80')

sio.wait()