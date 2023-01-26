import socket

def convert_to_celsius(fahrenheit):
	celsius = (fahrenheit - 32) * 5/9
	return celsius

#create ip
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#bind socket
server_address = ('192.168.217.135', 8080)
print('starting on 192.168.217.135)'.format(*server_address))
sock.bind(server_address)

sock.listen(1)
while True:
	print('waiting connection')
	connection, client_address = sock.accept()
	try:
		print('connection from', client_address)
		while True:
			data = connection.recv(16)
			if data:
				fahrenheit = float(data.decode())
				celsius = convert_to_celsius(fahrenheit)
				connection.sendall(str(celsius).encode())
			else:
				print('no more data from', client_address)
				break
	finally:
		connection.close()
