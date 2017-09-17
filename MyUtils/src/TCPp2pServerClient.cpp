/*
 * P2pServerClient.cpp
 *
 *  Created on: May 19, 2017
 *      Author: user
 */

#include "TCPp2pServerClient.h"

TCPp2pServerClient::TCPp2pServerClient(int port) {
	sock = new TCPSocket(port);
	serverSock = NULL;
	isServer = true;
}

TCPp2pServerClient::TCPp2pServerClient(string peerIp,int port) {
	sock = new TCPSocket(peerIp, port);
	serverSock = NULL;
	isServer = false;
}

void TCPp2pServerClient::run(){
	if(isServer){
		serverSock = sock->listenAndAccept();

		if(serverSock != NULL){
			char msg[1000];

			while(serverSock->recv(msg, 1000) > 0){
				cout<<"server: "<<msg<<endl;
			}
		}
	}
	else{
		if(sock != NULL){
			char msg[1000];

			while(serverSock->recv(msg, 1000) > 0){
				cout<<"client: "<<msg<<endl;
			}
		}
	}
}

TCPSocket* TCPp2pServerClient::getSock(){
	return sock;
}

TCPSocket* TCPp2pServerClient::getServerSock(){
	return this->serverSock;
}

void TCPp2pServerClient::setSock(TCPSocket* sock){
	this->sock = sock;
}

void TCPp2pServerClient::setServerSock(TCPSocket* serverSock){
	this->serverSock = serverSock;
}

TCPp2pServerClient::~TCPp2pServerClient() {
	if(sock != NULL){
		sock->close();
		delete(sock);
	}

	if(serverSock != NULL){
		serverSock->close();
		delete(sock);
	}
}

