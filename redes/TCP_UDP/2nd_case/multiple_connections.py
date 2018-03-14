import socket
import time
from threading import Thread, Lock

def beClient(HOST, PORT, size):
	dest = (str(HOST), PORT)
	beginning = time.time()
	for msgs in range(10000):
		tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		tcp.connect(dest)
		tcp.send(str.encode(' '*size))
		msg = tcp.recv(1024)
		tcp.close()
	print time.time() - beginning

clients = []
for i in range(20):
	clients.append(Thread(target = beClient, args = ('192.168.0.23', 1100, 32)))
for t in clients:
	t.start()
