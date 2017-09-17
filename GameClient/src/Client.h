/*
 * Client.h
 *
 *  Created on: Sep 7, 2017
 *      Author: user
 */

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include <iostream>
#include <string.h>
#include <vector>
#include "MThread.h"
#include "Protocol.h"
#include "TCPSocket.h"
#include "TheDogGame.h"

using namespace std;
using namespace game;
using namespace networkingLab;

namespace gameClient {

class Client:MThread{
private:
	TCPSocket* socket;
	string my_userName;
	string my_password;
	vector<string> usersRequests;
	int my_command;
	bool wait = false;
	bool stop;
public:
	Client();
	bool registerUser(string userName,string password);
	bool singIn(string userName,string password);

	string getActiveUsers();
	void sendGameRequst(string userName);
	void randomPlay();
	bool getGameRequst(string userName);
	vector<string> split(string toSplit,char splitBy);

	void start_game();

	void sendCommand(TCPSocket* peer,int command);
	void sendData(TCPSocket* peer,string data);
	int readCommand(TCPSocket* peer);
	string readData(TCPSocket* peer);

	void gameRequestsExsits();
	vector<string> getUsersRequests();
	virtual void run();
	void close();
	bool isAlive();
	virtual ~Client();
};

} /* namespace gameClient */

#endif /* SRC_CLIENT_H_ */
