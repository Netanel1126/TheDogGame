/*
 * TheHuntingGameServer.h
 *
 *  Created on: Aug 10, 2017
 *      Author: user
 */

#ifndef SRC_THEDOGGAMESERVER_H_
#define SRC_THEDOGGAMESERVER_H_

#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "User.h"
#include "MThread.h"
#include "Protocol.h"
#include "TCPSocket.h"
#define priorityQueue priority_queue<ScoreBoard,std::vector<ScoreBoard>,myComparison>

using namespace std;
using namespace networkingLab;

namespace gameServer {

struct ScoreBoard {
	int score;
	string userName;
};

class ClientHendler;

class myComparison {
	bool reverse;
public:
	myComparison(const bool& revparam = false) {
		reverse = revparam;
	}
	bool operator()(const ScoreBoard &lhs, const ScoreBoard &rhs) const {
		if (reverse)
			return (lhs.score > rhs.score);
		else
			return (lhs.score < rhs.score);
	}
};

class TheDogGameServer: MThread {
private:
	priorityQueue scoreBoard;
	vector<User> users;
	map<string, ClientHendler*> activeUsers;
	TCPSocket* TCPServer;
	bool stop;
public:
	TheDogGameServer();
	void AddUser(User user);
	bool userExsist(User user);
	void writeUsers();
	void readUsers();

	void writeScoreBoard(priorityQueue pq);
	priorityQueue readScoreBoard();
	void sendScoreBoard(TCPSocket* socket, string userName);
	void addToScoreBoard(string userName, int score);

	void sendActiveUser(TCPSocket* socket);
	void conectToUser(string userName, ClientHendler* User);
	void sendConectionRequst(string userName, ClientHendler* user);
	void refusedConection(string myUserName, string toSend);
	void removeFromeActiveUsers(string userName);
	void sendMsgToClient(TCPSocket* peer, string msg);
	void sendCommand(TCPSocket* peer, int command);
	User getUser(TCPSocket* peer);
	void sendWelcomeBackMsg(TCPSocket* peer, string userName);

	void close();
	virtual ~TheDogGameServer();

	const map<string, ClientHendler*>& getActiveUsers() const;
	void addActiveUser(string userName, ClientHendler* hendler);
	vector<User>& getUsers();
	void setUsers(const vector<User>& users);

	virtual void run();
};

class ClientHendler: MThread {
private:
	bool stop;
	string myUserName;
	TCPSocket* socket;
	TheDogGameServer* server;
public:
	ClientHendler(TCPSocket* socket, TheDogGameServer* server,
			string myUserName);
	int readCommand(TCPSocket* peer);
	string readData(TCPSocket* peer);
	void statThread();
	TCPSocket* getSocket();
	string getMyUserName();
	string commandToString(int command,string userName);
	virtual void run();
	virtual ~ClientHendler();
};

}
#endif /* SRC_THEDOGGAMESERVER_H_ */
