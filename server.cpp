#include <iostream>
#include <sstream> 
#include <chrono>
#include <thread>
#include <cstdlib>
#include <list>
#include <algorithm> // find()
#include "lib/UniSocket.hpp"
using namespace std;
    
#define POLLINGMYSEC 500000

list<UniSocket> clientConnections;

void threadHandle(UniSocket usock) {
	string msg;
	bool newMessage;
	
	try {
		cout << "hello " << usock.getIp() 
			<< ":" << usock.getPeerPort() 
			<< endl;
	} catch(UniSocketException & e) {
		cout << e._msg << endl;
	}
	
	while(true) {
		stringstream ss;
		try {
			msg = usock.recv(true);
			ss << "client " << usock.getIp() 
				<< ":" << usock.getPeerPort() 
				<< " says: " << msg;
			
			newMessage = true;
			if (msg == (string) ":q") break;
		} catch(UniSocketException & e) {
			this_thread::sleep_for(chrono::microseconds(POLLINGMYSEC));
			newMessage = false;
		}
		
		if (newMessage == false) continue;
		
		// need iterator to erase !!
		//for (auto &so : clientConnections) { so.send(ss.str()); ....
		
		for (auto i = clientConnections.begin(); i != clientConnections.end(); ) {
			try {
				cout << "      try to send '" << msg << "' to " 
					<< i->getIp() << ":" << i->getPeerPort() << endl;
				i->send(ss.str());
				++i;
			} catch (UniSocketException & e) {
				cout << "ups!  " 
					<< i->getIp() << ":" << i->getPeerPort() 
					<< " " << e._msg << endl;
				i = clientConnections.erase(i);
			}
		}
	}
	
	try {
		cout << "bye   " << usock.getIp() << ":" << usock.getPeerPort() << endl;
		
		auto iter = find_if(
			clientConnections.begin(), 
			clientConnections.end(),
			[&]( UniSocket us ) {
				if (
					( usock.getIp() == us.getIp() ) &&
					( usock.getPeerPort() == us.getPeerPort() )
				) {
					return true;
				} else {
					return false;
				}
			}
		);
		
		usock.close();
		clientConnections.erase(iter);
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
