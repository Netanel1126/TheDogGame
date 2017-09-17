/*
 * TCPp2pMessenger.h
 *
 *  Created on: May 19, 2017
 *      Author: user
 */

#ifndef SRC_TCPP2PMESSENGER_H_
#define SRC_TCPP2PMESSENGER_H_

#include "MThread.h"
#include "TCPp2pServerClient.h"

using namespace networkingLab;

class TCPp2pMessenger {
private:
	TCPp2pServerClient* p2pServer;
	TCPp2pServerClient* p2pClient;
public:
	TCPp2pMessenger(int port);
	bool open(string peerIp,int port);
	void send(string msg);
	void reply (string msg);
	void close();
	bool isActiveClientSession();
	bool isActivePeerSession();
};

#endif /* SRC_TCPP2PMESSENGER_H_ */
