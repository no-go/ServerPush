#include <iostream>
#include <string>
#include <cstdlib>
#include "lib/UniSocket.hpp"
using namespace std;

int main(int argc, char * argv[]) {
	if (argc < 4) {
		cout<<"usage: "<<argv[0]<<" <ip> <port> <message>"<<endl;
		return 1;
	}
	
	string msg = "";
	try {
		UniSocket s(argv[1], atoi(argv[2]));
		cout << "client port: " << s.getPort() << endl;
		s.send(argv[3]);
		
		while (msg != (string) "x") {
			// blocking read
			msg = s.recv();
			cout << "server says: " << msg << endl;
		}
		
		s.close();
	} catch(UniSocketException e) {
		cout << e._msg << endl;
	}
	
	return 0;
}
