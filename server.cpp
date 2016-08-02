#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <list>
#include "lib/UniSocket.hpp"
using namespace std;
    
#define POLLINGMYSEC 500000

list<UniSocket> clientConnections;

void threadHandle(UniSocket usock) {
	string msg;
	
	while(true) {
		try {
			msg = usock.recv(true);
			cout << "client "<< usock.getIp() << ":" << usock.getPeerPort() << " says: " << msg << endl;
			usock.send(msg);
			if (msg == (string) "x") break;
		} catch(UniSocketException & e) {
			this_thread::sleep_for(chrono::microseconds(POLLINGMYSEC));
		}
	}
	
	try {
		cout << "bye " << usock.getIp() << ":" << usock.getPeerPort() << endl;
		usock.close();
	} catch(UniSocketException & e) {
		cout << e._msg << endl;
	}
}

int main(int argc, char * argv[]) {
	if (argc < 2) {
		cout<<"usage: "<<argv[0]<<" <port>"<<endl;
		return 1;
	}
	try {
		UniServerSocket svr(atoi(argv[1]), 5);
		while (true) {
			UniSocket us = svr.accept();
			clientConnections.push_back(us);
			thread t(threadHandle, us);
			t.detach();
		}
	} catch(UniSocketException e) {
		cout << e._msg << endl;
	}
	return 0;
}
