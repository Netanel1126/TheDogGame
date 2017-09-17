/*
 * TCPSocket.h
 *
 *  Created on: Apr 24, 2017
 *      Author: user
 */

#ifndef SRC_TCPSOCKET_H_
#define SRC_TCPSOCKET_H_

#include <strings.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <fstream>


using namespace std;
namespace networkingLab {
class TCPSocket {
private:
	struct sockaddr_in serv_name;
	struct sockaddr_in cli_name;
public:
	int sock;
	TCPSocket();
	TCPSocket(int port);
	TCPSocket(string peerIp, int port);

	TCPSocket* listenAndAccept();

	int recv(char* buffer,int length);
	int send(const char* msg,int len);

	string fromAddr();
	string getAddr();

	void close();
	void clean_up(int cond, int *sock);

	int getSock();
	void setSock(int sock);
	virtual ~TCPSocket();
};
}

#endif /* SRC_TCPSOCKET_H_ */
