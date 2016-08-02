#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include "lib/UniSocket.hpp"
using namespace std;

void threadHandle(UniSocket usock, string pingMsg) {
	usock.send(pingMsg);
	try {
		while (pingMsg != (string) ":q") {
			// blocking read
			pingMsg = usock.recv();
			cout << pingMsg << endl;
		}
		usock.close();
	} catch(UniSocketException e) {
		cout << e._msg << endl;
	}
}

int main(int argc, char * argv[]) {
	if (argc < 4) {
		cout<<"usage: "<<argv[0]<<" <ip> <port> <first message>"<<endl;
		return 1;
	}
	
	string msg = argv[3];
	
	try {
		UniSocket s(argv[1], atoi(argv[2]));
		cout << " You are "<< s.getIp() << ":"<< s.getPort() << endl;
		cout << " Please type your messages. Type :q for exit." << endl;
		cout << "----------------------------------------------" << endl;
		
		thread t(threadHandle, s, msg);
		
		while (msg != (string) ":q") {
			cin >> msg;
			s.send(msg);
		}
		// a :q close connection by server -> the thread mention it and does a close
		t.join();
		
	} catch(UniSocketException e) {
		cout << e._msg << endl;
	}
	
	return 0;
}
