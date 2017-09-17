/*
 * ClientTest.h
 *
 *  Created on: Sep 7, 2017
 *      Author: user
 */

#ifndef SRC_CLIENTTEST_H_
#define SRC_CLIENTTEST_H_

#include <iostream>
#include "MThread.h"
#include "Client.h"

using namespace std;
using namespace networkingLab;
using namespace gameClient;

class ClientTest:MThread{
private:
	TCPSocket* socket;
	bool successful;
	Client* c;
	Client* c1;
public:
	ClientTest();
	bool startTest();
	virtual void run();
	virtual ~ClientTest();
};

#endif /* SRC_CLIENTTEST_H_ */
