import socket
s = socket.socket()
print("Berjaya buat sokett")
port = 8080
s.bind(('',port))
print("Berjaya bind soket di port: " + str(port))
s.listen(5)
print("soket tengah menunggu client!")
while True:
	c,addr = s.accept()
	print("Dapat capaian dari: " + str(addr))
	buffer = c.recv(1024)
	print(buffer.decode())
	c.send(buffer + b' from server xyz')
	c.close()
