import socket
import select

IP = "127.0.0.1"
PORT = 1234

# Create a socket
# socket.AF_INET - address family, IPv4, some otehr possible are AF_INET6, AF_BLUETOOTH, AF_UNIX
# socket.SOCK_STREAM - TCP, conection-based, socket.SOCK_DGRAM - UDP, connectionless, datagrams, socket.SOCK_RAW - raw IP packets
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# SO_ - socket option
# SOL_ - socket option level
# Sets REUSEADDR (as a socket option) to 1 on socket
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# Bind, so server informs operating system that it's going to use given IP and port
# For a server using 0.0.0.0 means to listen on all available interfaces, useful to connect locally to 127.0.0.1 and remotely to LAN interface IP
server_socket.bind((IP, PORT))

# This makes server listen to new connections
server_socket.listen()

# List of sockets for select.select()
sockets_list = [server_socket]

# List of connected clients - socket as a key, user header and name as data
clients = {}

print(f'Listening for connections on {IP}:{PORT}...')


def receive_message(client_socket, client_address):
	full_msg = ''
	length = 0
	msg = client_socket.recv(3)
	msg = msg.decode("utf-8")
	length = int(msg)
	msg2 = client_socket.recv(length)
	full_msg += msg2.decode("utf-8")
	addr_string = str(client_address)
	return {'addr': addr_string, 'data': full_msg}

while True:
	# Calls Unix select() system call or Windows select() WinSock call with three parameters:
    #   - rlist - sockets to be monitored for incoming data
    #   - wlist - sockets for data to be send to (checks if for example buffers are not full and socket is ready to send some data)
    #   - xlist - sockets to be monitored for exceptions (we want to monitor all sockets for errors, so we can use rlist)
    # Returns lists:
    #   - reading - sockets we received some data on (that way we don't have to check sockets manually)
    #   - writing - sockets ready for data to be send thru them
    #   - errors  - sockets with some exceptions
    # This is a blocking call, code execution will "wait" here and "get" notified in case any action should be taken
	read_sockets, _, exception_sockets = select.select(sockets_list, [], sockets_list)

	# Iterate over notified sockets
	for notified_socket in read_sockets:

        # If notified socket is a server socket - new connection, accept it
		if notified_socket == server_socket:
			# Accept new connection
            # That gives us new socket - client socket, connected to this given client only, it's unique for that client
            # The other returned object is ip/port set
			client_socket, client_address = server_socket.accept()
			
			#print(f"Connection from {client_address} has been established.")
			
			# Client should send his name right away, receive it
			user = receive_message(client_socket, client_address)

			 # If False - client disconnected before he sent his name
			if user is False:
				continue

            # Add accepted socket to select.select() list
			sockets_list.append(client_socket)

            # Also save username and username header
			clients[client_socket] = user

			print('Accepted new connection from {}, username: {}'.format(user['addr'], user['data']))

			string_to_send = ""
			for x in clients.values():
  				if user['addr'] != x['addr']:
  					client_socket.send(bytes("Name:"+ x['data'] + "\nIP:" + x['addr'], "utf-8"))

		# Else existing socket is sending a message
		else:

            # Receive message
			message = receive_message(notified_socket,"default") #address here does not metter.

            # If False, client disconnected, cleanup
			if message is False:
				print('Closed connection from: {}'.format(clients[notified_socket]['data']))

                # Remove from list for socket.socket()
				sockets_list.remove(notified_socket)

                # Remove from our list of users
				del clients[notified_socket]

				continue

            # Get user by notified socket, so we will know who sent the message
			user = clients[notified_socket]

			print(f'Received message from {user["data"]}: {message["data"]}')

            # Iterate over connected clients and broadcast message
			for client_socket in clients:

                # But don't sent it to sender
				if client_socket != notified_socket:

                    # Send user and message (both with their headers)
                    # We are reusing here message header sent by sender, and saved username header send by user when he connected
					client_socket.send(bytes(message['data'], "utf-8"))