/*
 * TCPSocket.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: user
 */

#include "TCPSocket.h"

using namespace std;
using namespace networkingLab;

TCPSocket::TCPSocket(){
	bzero((char*)&serv_name, sizeof(serv_name));
	bzero((char*)&cli_name, sizeof(cli_name));
}

TCPSocket::TCPSocket(int port) {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0){
		perror ("Error opening channel");
		clean_up(1, &sock);
	}
	bzero((char*)&serv_name, sizeof(serv_name));

	serv_name.sin_family = AF_INET;
	serv_name.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_name.sin_port = htons(port);

	if (bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name)) < 0){
		perror ("Error naming channel");
		clean_up(1, &sock);
	}
	printf("Server is alive and waiting for socket connection from client.\n");
	listen(sock,1);
}

TCPSocket::TCPSocket(string peerIp, int port){
	sock = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0){
		perror ("Error opening channel");
		clean_up(1, &sock);
	}
	bzero((char*)&cli_name, sizeof(cli_name));

	cli_name.sin_family = (short)AF_INET;
	cli_name.sin_addr.s_addr = inet_addr(peerIp.data());
	cli_name.sin_port = htons((u_short)port);

	if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
	{
		perror ("Error establishing communications");
		clean_up(1, &sock);
	}
}

TCPSocket::~TCPSocket() {
}

TCPSocket* TCPSocket::listenAndAccept(){
	TCPSocket* tcp_sock = new TCPSocket();
	int rc = listen(sock, 1);

	if(rc < 0){
		printf("ERROR");
		return NULL;
	}
	socklen_t len = sizeof(cli_name);
	bzero((char*) &cli_name, sizeof(cli_name));
	int connect_sock = accept(sock, (struct sockaddr *)&cli_name, &len);
	tcp_sock->sock = connect_sock;
	tcp_sock->serv_name = this->serv_name;
	tcp_sock->cli_name = this->cli_name;
	return tcp_sock;
}

int TCPSocket::recv(char* buffer,int length){
	return read(sock, buffer, length);
}

int TCPSocket::send(const char* msg,int len){
	return write(sock, msg, len);
}

void TCPSocket::close(){
	::close(sock);
}

string TCPSocket::fromAddr(){
	return inet_ntoa(cli_name.sin_addr);
}

void TCPSocket::clean_up(int cond,int* sock){
  cout<<"Exiting now.\n"<<endl;
  ::close(*sock);
  exit(cond);
}

int TCPSocket::getSock(){
	return this->sock;
}

string TCPSocket::getAddr(){
	return inet_ntoa(serv_name.sin_addr);
}

void TCPSocket::setSock(int sock){
	this->sock = sock;
}
