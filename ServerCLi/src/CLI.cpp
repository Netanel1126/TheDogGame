/*
 * CLI.cpp
 *
 *  Created on: Sep 16, 2017
 *      Author: user
 */

#include "CLI.h"

CLI::CLI() {
	server = new TheDogGameServer;
	loadAdmin();
}


void CLI::startCLI(){
	string command;

	do{
		cout<<"What would you like to do?\n"
				"Enter 'A' to see all active users\n"
				"Enter 'U' to see all of the Users\n"
				"Enter 'S' to see the ScoreBoard\n"
				"Enter 'K' + activeUser to remove him\n"
				"Enter 'end' to stop the server"<<endl;
		cin>>command;

		if(command == "A" ||command == "a"){
			server->sendCommand(admin, getAllConnectedUsers);
			c->readCommand(admin);
			cout<<c->readData(admin)<<endl;
		}else if(command == "U" ||command == "u"){
			vector<User> users = server->getUsers();
			cout<<"Users"<<endl;

			for (int i = 0; i < users.size(); i++)
				cout<<users[i].getUserName()<<endl;

		}else if(command == "S" ||command == "s"){
			server->sendCommand(admin, getScoreboard);
			c->readCommand(admin);
			cout<<c->readData(admin)<<endl;

		}else if(command == "K" ||command == "k"){
			cin>>command;
			server->removeFromeActiveUsers(command);

		}else if(command != "end"){
			cout<<"ERROR - Command not found"<<endl;
		}
	}while(command != "end");
	cout<<"Bye"<<endl;
	server->close();
}

void CLI::loadAdmin(){
	User user;
	int command = newUser;
	user.setUser("admin", "admin");
	if(server->userExsist(user))
		command = loadUser;

	admin = new TCPSocket("127.0.0.1", 1126);
	server->sendCommand(admin, command);
	server->sendMsgToClient(admin, "admin");
	server->sendMsgToClient(admin, "admin");
	cout<<c->readData(admin)<<endl;
}

CLI::~CLI() {
	// TODO Auto-generated destructor stub
}

