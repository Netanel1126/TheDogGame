/*
 * MultipleTCPSocketsListener.h
 *
 *  Created on: Feb 14, 2013
 *      Author: efi
 */

#ifndef MULTIPLETCPSOCKETSLISTENER_H_
#define MULTIPLETCPSOCKETSLISTENER_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include "TCPSocket.h"

using namespace std;
using namespace networkingLab;

class MultipleTCPSocketsListener{
private:
	vector<TCPSocket*> vSocket;
public:
	/*
	 * Add the given socket to the socket list to be listen on
	 */
	void addSocket(TCPSocket* socket);

	/*
	 * Set the given sockets to the socket list to be listen on
	 */
	void addSockets(vector<TCPSocket*> socketVec);

	/*
	 * This method checks to see if any of the previous given sockets are ready for reading
	 * It returns one of the Sockets that are ready.
	 */
	TCPSocket* listenToSocket();
};

#endif /* MULTIPLETCPSOCKETSLISTENER_H_ */
