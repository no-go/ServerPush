#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include "lib/UniSocket.hpp"
using namespace std;

void threadHandle(UniSocket usock, string pingMsg) {
	usock.send(pingMsg);
	while (pingMsg != (string) ":q") {
		// blocking read
		pingMsg = usock.recv();
		cout << pingMsg << endl;
	}
	usock.close();
}

int main(int argc, char * argv[]) {
	if (argc < 4) {
		cout<<"usage: "<<argv[0]<<" <ip> <port> <message>"<<endl;
		return 1;
	}
	
	string msg = argv[3];
	
	try {
		UniSocket s(argv[1], atoi(argv[2]));
		cout << "I am "<< s.getIp() << ":"<< s.getPort() << endl;
		
		thread t(threadHandle, s, msg);
		t.join();
		
	} catch(UniSocketException e) {
		cout << e._msg << endl;
	}
	
	return 0;
}
