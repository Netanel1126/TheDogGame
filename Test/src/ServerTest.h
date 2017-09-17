/*
 * ServerTest.h
 *
 *  Created on: Sep 2, 2017
 *      Author: user
 */

#ifndef SERVERTEST_H_
#define SERVERTEST_H_

#include <iostream>
#include "TCPSocket.h"

#include "TheDogGameServer.h"

using namespace std;
using namespace networkingLab;
using namespace gameServer;

class ServerTest {
private:
	TCPSocket* client1;
	TCPSocket* client2;
	TCPSocket* client3;
	ClientHendler* c;
	int command;
	string msg,buffer;
	TheDogGameServer *gameServer;

public:
	ServerTest();
	bool startTest();
	virtual ~ServerTest();
};

#endif /* SERVERTEST_H_ */
