/*
 * ClientTest.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: user
 */

#include "ClientTest.h"

ClientTest::ClientTest() {
	successful = false;
	this->start();
	sleep(2);
	c = new Client;
}

bool ClientTest::startTest(){
	string buffer;
	int command;

	if(!(c->registerUser("test12", "test12")))
		return false;

	c->randomPlay();
	sleep(15);
	c->close();
	if(!successful)
		return false;

	return true;
}

void ClientTest::run(){
	string buffer;
	TCPSocket* t = new TCPSocket(1126);
	socket = t->listenAndAccept();

	int command = c->readCommand(socket);
	if(command != newUser)
		return;

	buffer = c->readData(socket);
	cout<<"1ClintTest: "<<buffer<<endl;
	if(buffer != "test12")
		return;

	buffer = c->readData(socket);
	cout<<"2ClintTest: "<<buffer<<endl;
	if(buffer != "test12")
		return;

	c->sendData(socket,"Bla Bla");

	command = c->readCommand(socket);
	if(command != getAllConnectedUsers)
		return;

	c->sendCommand(socket, getAllConnectedUsers);
	c->sendData(socket, "Active Users\n"
			"test1\n"
			"test2\n"
			"test12");

	command = c->readCommand(socket);
	if(command != connectToUser)
		return;

	buffer = c->readData(socket);
	cout<<"3ClintTest: "<<buffer<<endl;

	c->sendCommand(socket, connectToUser);
	c->sendData(socket, "test");

	sleep(2);
	c->gameRequestsExsits();

	command = c->readCommand(socket);
	if(command != refusedConnection)
		return;

	buffer = c->readData(socket);
	if(buffer != "test")
		return;

	successful = true;
}

ClientTest::~ClientTest() {
	delete c;
}

