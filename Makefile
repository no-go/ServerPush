
all: socket server client

socket:
	g++ -Wall -g -std=c++11 -c lib/UniSocket.cpp -o lib/UniSocket.o
	g++ -Wall -g -std=c++11 -c lib/SocketWrapperLinux.cpp -o lib/SocketWrapperLinux.o

server:
	g++ -Wall -std=c++11 -c server.cpp
	g++ -Wall -g -std=c++11 -pthread -o serverLinux server.o lib/SocketWrapperLinux.o lib/UniSocket.o

client:
	g++ -Wall -std=c++11 -pthread -c client.cpp
	g++ -Wall -g -std=c++11 -pthread -o clientLinux client.o lib/SocketWrapperLinux.o lib/UniSocket.o

clean:
	rm -f clientLinux serverLinux
	rm -f *.o
	rm -f lib/*.o
