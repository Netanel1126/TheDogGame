/*
 * ClientCLI.cpp
 *
 *  Created on: Sep 9, 2017
 *      Author: user
 */

#include "ClientCLI.h"

ClientCLI::ClientCLI() {
	client = new Client;
}

string ClientCLI::showCommand() {
	string command;
	cout
			<< "Please choose what you would like to do:\n"
					"Enter 'a' to get Active Users\n"
					"Enter 'r' for a Random Game\n"
					"Enter 's' + UserName to send game request\n"
					"Enter 'e' to Exit"
			<< endl;
	cin >> command;
	return command;
}

void ClientCLI::startCLI() {
	string command, userName, password;
	cout
			<< "Welcome!!!\n"
					"Enter 's' to sign in\n"
					"Enter 'n' for new user\n"
					"Enter 'e' to Exit"
			<< endl;
	cin >> command;

	while (command != "e") {
		cout << "Enter UserName" << endl;
		cin >> userName;
		cout << "Enter password" << endl;
		cin >> password;

		if (command == "n") {
			if (client->registerUser(userName, password))
				break;
		} else if (command == "s") {
			if (client->singIn(userName, password)) {
				break;
			}
		} else
			cout << "ERROR - Command Not Found Try Again" << endl;

		if(!client->isAlive())
			break;

		cout<<"Enter 'e' to Exit else enter 'c'"<< endl;
		string temp;
		cin >> temp;
		if(temp == "e")
			break;
	}
	if (command == "e" || !client->isAlive()) {
		close();
		return;
	}
	this->CLI();
}

void ClientCLI::CLI() {
	string commands;
	string buffer = "empty";

	do {
		client->gameRequestsExsits();
		commands = showCommand();
		if (commands == "a") {
			buffer = client->getActiveUsers();
			cout << buffer << endl;
		}

		else if (commands == "r") {
			client->randomPlay();
		}

		else if (commands == "s") {
			cin>>commands;
			client->sendGameRequst(commands);
		}

		else if (commands == "e") {
			cout << "Bye" << endl;
		}

		else
			cout << "ERROR - Command Not Found Try Again" << endl;
	} while (commands != "e");

	close();
}

void ClientCLI::close(){
	client->close();
}

ClientCLI::~ClientCLI() {
	// TODO Auto-generated destructor stub
}

