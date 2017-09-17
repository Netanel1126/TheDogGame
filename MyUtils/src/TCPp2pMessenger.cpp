/*
 * TCPp2pMessenger.cpp
 *
 *  Created on: May 19, 2017
 *      Author: user
 */

#include "TCPp2pMessenger.h"
using namespace networkingLab;

TCPp2pMessenger::TCPp2pMessenger(int port) {
	p2pServer = new TCPp2pServerClient(port);
	p2pClient = NULL;
	p2pServer->start();

	sleep(1);
}

bool TCPp2pMessenger::open(string peerIp,int port){
	if(isActiveClientSession()){
		p2pClient->getSock()->close();
		p2pClient->waitForThread();

		delete(p2pClient);
		p2pClient = NULL;
	}

	p2pClient = new TCPp2pServerClient(peerIp,port);
	p2pClient->start();

	if(p2pClient == NULL)
		return false;

	return true;
}

void TCPp2pMessenger::send(string msg){
	if(isActiveClientSession()){
		perror("ERROR - Not Connected");
		return;
	}

	p2pClient->getSock()->send(msg.substr(0,4).c_str(), sizeof(msg.substr(0,4).c_str()));
}

void TCPp2pMessenger::reply(string msg){
	if(isActivePeerSession()){
		perror("ERROR - Not Connected");
		return;
	}

	p2pServer->getServerSock()->send(msg.substr(0,4).c_str(), sizeof(msg.substr(0,4).c_str()));
}

void TCPp2pMessenger::close(){
	if(p2pServer != NULL)
		delete p2pServer;
	if(p2pClient != NULL)
		delete p2pClient;
}

bool TCPp2pMessenger::isActiveClientSession(){
	if(p2pClient->getSock() == NULL)
		return false;

	return true;
}

bool TCPp2pMessenger::isActivePeerSession(){
	if(p2pServer->getSock() == NULL || p2pServer->getServerSock() == NULL)
		return false;

	return true;
}

