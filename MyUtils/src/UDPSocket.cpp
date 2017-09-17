/*
 * UDPSocket.cpp
 *
 *  Created on: Apr 3, 2017
 *      Author: user
 */

#include "UDPSocket.h"
#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

namespace networkingLab {

UDPSocket::~UDPSocket() {
	// TODO Auto-generated destructor stub
}

UDPSocket::UDPSocket(int port) {
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *) &s_in, sizeof(s_in));
	s_in.sin_family = (short)AF_INET;
	s_in.sin_addr.s_addr = htonl(INADDR_ANY);
	s_in.sin_port = htons(port);
	n = 0;
	fsize = 0;

	if (bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in))<0)
		perror("Error naming channel");
}

int UDPSocket::recv(char* buffer, int length) {
	fsize = sizeof(remote);

	n = (int)recvfrom(socket_fd,buffer,(unsigned long int)length,0,(struct sockaddr *)&remote,&fsize);
	if (n < 0){
		perror("recvfrom");
		return 0;
	}
	return n;
}

int UDPSocket::sendTo(const string msg,const string ip, int port) {
	remote.sin_family = (short)AF_INET;
	remote.sin_addr.s_addr = inet_addr(ip.c_str()); /* WILDCARD any system ip*/
	remote.sin_port = htons(port);

	n = sendto(socket_fd,msg.data(), msg.length(),0,(struct sockaddr*)&remote,sizeof(remote));
	if (n < 0){
		perror("Sendto");
		return 0;
	}
	return n;
}

int UDPSocket::reply(string msg) {
	n = sendto(socket_fd,msg.data(), msg.length(),0,(struct sockaddr*)&s_in,sizeof(s_in));
	return n;
}

void UDPSocket::close() {
	shutdown(socket_fd,SHUT_RDWR);
	::close(socket_fd);
}

string UDPSocket::fromAddr() {
	return inet_ntoa(remote.sin_addr);
}

} 
