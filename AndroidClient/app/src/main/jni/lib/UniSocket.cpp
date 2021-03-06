#include <string>
#include "UniSocket.hpp"

UniSocketException::UniSocketException(std::string msg) {
	_msg = msg;
}

// primary client methods -----------------

UniSocket::UniSocket(
	const std::string & ip,
	const int & port
) {
	_ip = ip;
	_sock = SocketWrapper(_ip, port);
}

void UniSocket::send(const std::string & data) {
	_sock.send(data);
}

std::string UniSocket::recv(bool polling) {
	return _sock.recv(polling);
}

void UniSocket::close(void) {
	_sock.close();
}
std::string UniSocket::getIp(void) {
	return _ip;
}

int UniSocket::getPort(void) {
	return _sock.getPort();
}

// very useful for a server -----------------

int UniSocket::getPeerPort(void) {
	return _sock.getPeerPort();
}

UniSocket::UniSocket(void) {}

UniSocket::UniSocket(const UniSocket & ref) {
	_ip = ref._ip;
	_sock = ref._sock;
}

UniSocket::UniSocket(
 const std::string & ip,
 const SocketWrapper & sock) {
	_ip = ip;
	_sock = sock;
}

UniServerSocket::UniServerSocket(
	const int & port,
	const int & queueSize
) {
	_port = port;
	_ssock = SocketWrapper(port, queueSize);
}

UniServerSocket::~UniServerSocket(void) {
	_ssock.close();
}

UniSocket UniServerSocket::accept(void) {
	SocketWrapper sw = _ssock.accept();
	UniSocket us = UniSocket(sw._ip, sw);
	return us;
}

int UniServerSocket::getPort(void) {
	return _port;
}
