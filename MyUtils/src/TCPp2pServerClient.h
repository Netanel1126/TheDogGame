/*
 * P2pServerClient.h
 *
 *  Created on: May 19, 2017
 *      Author: user
 */

#ifndef SRC_TCPP2PSERVERCLIENT_H_
#define SRC_TCPP2PSERVERCLIENT_H_

#include "TCPSocket.h"
#include <iostream>
#include "MThread.h"

using namespace std;
using namespace networkingLab;

class TCPp2pServerClient:public MThread{
private:
	TCPSocket* serverSock;
	TCPSocket* sock;
	bool isServer;
public:
	TCPp2pServerClient(int port);
	TCPp2pServerClient(string peerIp,int port);
	void run();

	TCPSocket* getServerSock();
	TCPSocket* getSock();

	void setServerSock(TCPSocket* serverSock);
	void setSock(TCPSocket* sock);

	~TCPp2pServerClient();
};

#endif /* SRC_TCPP2PSERVERCLIENT_H_ */
