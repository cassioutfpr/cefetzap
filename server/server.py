import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print(f"hostname{socket.gethostname()}")
s.bind(("127.0.0.1", 80))
s.listen(5)

while True:
    # now our endpoint knows about the OTHER endpoint.
    clientsocket, address = s.accept()
    print(f"Connection from {address} has been established.")
    clientsocket.send(bytes("ALOU MUNDAO","utf-8"))