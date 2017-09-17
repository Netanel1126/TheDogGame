/*
 * ServerTest.cpp
 *
 *  Created on: Sep 2, 2017
 *      Author: user
 */

#include "ServerTest.h"
#include "Protocol.h"

ServerTest::ServerTest() {
	gameServer = new TheDogGameServer;
}

bool ServerTest::startTest() {
	User user;
	user.setUser("test", "test");
	gameServer->AddUser(user);
	gameServer->writeUsers();

	gameServer->addToScoreBoard("jeff", 120);
	gameServer->addToScoreBoard("dan", 300);


	//create new client
	client1 = new TCPSocket("127.0.0.1", 1126);
	sleep(2);

	//add new user
	command = newUser;
	gameServer->sendCommand(client1, command);

	gameServer->sendMsgToClient(client1, "test1");
	gameServer->sendMsgToClient(client1, "test1");

	cout<<c->readData(client1)<<endl;

	//get all connected users
	command = getAllConnectedUsers;
	gameServer->sendCommand(client1, command);

	cout<<c->commandToString(c->readCommand(client1),"TestServer")<<endl;
	buffer = c->readData(client1);
	cout << buffer << endl;

	if (buffer != "Active Users\n"
			"test1\n")
		return false;
	command = getScoreboard;
	gameServer->sendCommand(client1, command);

	cout<<c->commandToString(c->readCommand(client1),"TestServer")<<endl;
	buffer = c->readData(client1);
	cout<<buffer<<endl;
	if(buffer != "Scoreboard\n"
			"dan Score: 300\njeff Score: 120\n")
		return false;

	//create new client
	client2 = new TCPSocket("127.0.0.1", 1126);

	//try to conceit with a user that dosn't exist
	command = loadUser;
	gameServer->sendCommand(client2, command);

	for (int i = 0;  i < 2; ++ i) {
		gameServer->sendMsgToClient(client2, "test2");
		gameServer->sendMsgToClient(client2, "test2");

		buffer = c->readData(client2);
		if(buffer != "User doesn't exist please try again")
			return false;
		gameServer->sendCommand(client2, command);
	}

	gameServer->sendMsgToClient(client2, "test2");
	gameServer->sendMsgToClient(client2, "test2");
	buffer = c->readData(client2);

	if(buffer != "Kill")
		return false;

	client3 = new TCPSocket("127.0.0.1", 1126);
	command = loadUser;
	gameServer->sendCommand(client3, command);
	gameServer->sendMsgToClient(client3, "test");
	gameServer->sendMsgToClient(client3, "test");
	buffer = c->readData(client3);
	if(buffer != "Welcome Back test")
		return false;

	command = getAllConnectedUsers;
	gameServer->sendCommand(client3, command);
	cout<<c->commandToString(c->readCommand(client3),"TestServer")<<endl;
	buffer = c->readData(client3);
	cout<<buffer<<endl;

	command = connectToUser;
	gameServer->sendCommand(client3, command);
	gameServer->sendMsgToClient(client3, "test3");
	buffer = c->readData(client3);
	cout<<buffer<<endl;
	if(buffer != "ERROR - User doesn't exist")
		return false;

	command = connectToUser;
	gameServer->sendCommand(client3, command);
	gameServer->sendMsgToClient(client3, "test1");

	cout<<"Command:"<<c->readCommand(client1)<<endl;
	buffer = c->readData(client1);
	if(buffer != "test")
		return false;

	command = refusedConnection;
	gameServer->sendCommand(client1, command);
	gameServer->sendMsgToClient(client1, "test");

	cout<<c->readCommand(client3)<<endl;
	buffer = c->readData(client3);
	if(buffer != "test1 Refused Connection")
		return false;

	return true;
}

ServerTest::~ServerTest() {
	gameServer->close();
	delete gameServer;
	/*client1->close();
	client2->close();
	client3->close();*/
}

