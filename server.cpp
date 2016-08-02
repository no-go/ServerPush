#include <iostream>
#include <sstream> 
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
	
	try {
		cout << "hello " << usock.getIp() 
			<< ":" << usock.getPeerPort() 
			<< endl;
	} catch(UniSocketException & e) {
		cout << e._msg << endl;
	}
	
	while(true) {
		try {
			msg = usock.recv(true);
			stringstream ss;
			ss << "client " << usock.getIp() 
				<< ":" << usock.getPeerPort() 
				<< " says: " << msg;
			
			for (auto &so : clientConnections) {
				so.send(ss.str());
			}
			if (msg == (string) ":q") break;
		} catch(UniSocketException & e) {
			this_thread::sleep_for(chrono::microseconds(POLLINGMYSEC));
			/** @todo hier muss server irgendwann eine testnachricht 
			 * senden um verbindung zu testen oder sowas ??
			 */
		}
	}
	
	try {
		cout << "bye   " << usock.getIp() << ":" << usock.getPeerPort() << endl;
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
