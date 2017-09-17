/*
 * CLI.h

 *
 *  Created on: Sep 16, 2017
 *      Author: user
 */

#ifndef CLI_H_
#define CLI_H_

#include <iostream>
#include "TheDogGameServer.h"

using namespace std;
using namespace gameServer;

class CLI {
private:
	TheDogGameServer* server;
	TCPSocket* admin;
	ClientHendler* c;
public:
	CLI();
	void startCLI();
	void loadAdmin();
	virtual ~CLI();
};

#endif /* CLI_H_ */
