/*
 * ClientCLI.h
 *
 *  Created on: Sep 9, 2017
 *      Author: user
 */

#ifndef SRC_CLIENTCLI_H_
#define SRC_CLIENTCLI_H_

#include <iostream>
#include <string>
#include "Client.h"

using namespace std;
using namespace gameClient;


class ClientCLI {
private:
	Client* client;
public:
	ClientCLI();
	string showCommand();
	void startCLI();
	void CLI();
	void close();
	virtual ~ClientCLI();
};

#endif /* SRC_CLIENTCLI_H_ */
