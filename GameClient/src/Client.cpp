/*
 * Client.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: user
 */

#include "Client.h"
#include <sstream>

namespace gameClient {

Client::Client() {
	socket = new TCPSocket("127.0.0.1", 1126);
	stop = false;
}

bool Client::registerUser(string userName, string password) {
	string buffer;
	//send user name and password and waits for answer
	sendCommand(socket, newUser);
	sendData(socket, userName);
	sendData(socket, password);
	buffer = readData(socket);
	cout << buffer << endl;

	if (buffer == "User doesn't exist please try again")
		return false;

	my_userName = userName;
	my_password = password;
	this->start();
	return true;
}

bool Client::singIn(string userName, string password) {
	string buffer;
	//send user name and password and waits for answer
	sendCommand(socket, loadUser);
	sendData(socket, userName);
	sendData(socket, password);
	buffer = readData(socket);
	cout << buffer << endl;

	//if successful start thread and return true
	if (buffer == ("Welcome Back " + userName)) {
		my_userName = userName;
		my_password = password;
		this->start();
		return true;
	}
	if(buffer == "Kill"){
		cout<<"ERROR - Closing now"<<endl;
		this->stop = true;
	}
	return false;
}

string Client::getActiveUsers() {
	int command = getAllConnectedUsers;
	string buffer;

	sendCommand(socket, command);
	sleep(1);
	buffer = readData(socket);

	return buffer;
}

void Client::sendGameRequst(string userName) {
	sendCommand(socket, connectToUser);
	sendData(socket, userName);

	cout<<"Waiting for Answer..."<<endl;
	//command = readCommand(socket);
	while(my_command != startGame && my_command != refusedConnection){sleep(5);}
	if(my_command == startGame)
		start_game();
	else if(my_command == refusedConnection)
		cout << readData(socket) << endl;
	else
		cout<<"ERROR Command not found"<<endl;
}

void Client::randomPlay() {
	srand(time(NULL));
	vector<string> activeUsersV;
	string activeUsers = getActiveUsers();
	activeUsersV = split(activeUsers, '\n');

	//Removes "Active Users" and the user name from the vector
	activeUsersV.erase(activeUsersV.begin());

	for (int i = 0; i < activeUsersV.size(); i++) {
		if (activeUsersV[i] == my_userName)
			activeUsersV.erase(activeUsersV.begin() + i);
	}
	sendGameRequst(activeUsersV[rand() % activeUsersV.size()]);
}

vector<string> Client::split(string toSplit, char splitBy) {
	vector<string> divided;
	std::stringstream ss(toSplit.data());
	std::string to;

	if (toSplit.data() != NULL) {
		while (std::getline(ss, to, splitBy)) {
			divided.push_back(to);
		}
	}
	return divided;
}

bool Client::getGameRequst(string userName) {
	string buffer;
	cout << "User " << userName
			<< " would like to start a game do you agree?\n"
					"press y for Yes or n for No"
			<< endl;
	do {
		cin >> buffer;
		if (buffer == "y") {
			sendCommand(socket, acceptConnection);
			sendData(socket, userName);
			start_game();
			return true;
		} else if (buffer == "n") {
			sendCommand(socket, refusedConnection);
			sendData(socket, userName);
			return false;
		} else
			cout << "ERROR - Command not found try again" << endl;

	} while (buffer != "y" || buffer != "n");
}

void Client::start_game() {
	wait = true;
	string player2_ip = readData(socket);
	string player2_UserName = readData(socket);
	int my_port = readCommand(socket);
	int player2_port = readCommand(socket);
	string buffer;

	TheDogGame* game = new TheDogGame(socket->getAddr(), my_userName,
			my_port,player2_ip,player2_UserName,player2_port);

	int score = game->starGame();

	sendCommand(socket, addToScorebord);
	sendData(socket, my_userName);
	sendCommand(socket, score);

	cout << "Would you like to see the scoreBord\n"
			"press y for Yes or n for No"
			<< endl;
	cin >> buffer;

	if (buffer == "y") {
		sendCommand(socket, getScoreboard);
		cout << readData(socket) << endl;
	} else if (buffer != "n")
		cout << "ERROR - Command not found" << endl;
	wait = false;
}

void Client::sendCommand(TCPSocket* peer, int command) {
	int msgLen = htonl(command);
	peer->send((char*) &msgLen, 4);
}

void Client::sendData(TCPSocket* peer, string data) {
	int msgLen = htonl(data.length());
	peer->send((char*) &msgLen, 4);
	peer->send(data.data(), data.length());
}

int Client::readCommand(TCPSocket* peer) {
	int command;
	// Read a command from socket
	peer->recv((char*) &command, 4);
	return ntohl(command);
}

string Client::readData(TCPSocket* peer) {
	// Read a string from socket
	int length = readCommand(peer);
	// Receive the incoming message
	char buffer[length];
	memset((void*) buffer, 0, length);

	int rc = peer->recv(buffer, length);
	if (rc < 0) {
		perror("Error receiving socket");
		return "";
	}
	string str = buffer;
	return str.substr(0, length);
}

bool Client::isAlive(){
	return !stop;
}

void Client::run() {
	string data;

	while (!stop) {
		while(wait){sleep(10);}
		my_command = readCommand(socket);
		switch (my_command) {

		case connectToUser:
			usersRequests.push_back(readData(socket));
			break;

		case getAllConnectedUsers:
			sleep(2);
			break;

		case startGame:
			sleep(15);
			break;

		case getScoreboard:
			sleep(2);
			break;

		case Kill:
			close();
			break;

		default:
			cout << "ERROR - Command not found" << endl;
		}
	}
}

void Client::close() {
	stop = true;
	sendCommand(socket, Kill);
	this->stopThread();
	socket->close();
}

void Client::gameRequestsExsits(){

	if(usersRequests.empty())
		return;

	for(int i = 0;i < usersRequests.size(); i++){
		string userName = usersRequests[i];
		 usersRequests.erase(usersRequests.begin());
		if(getGameRequst(userName))
			return;
	}
}

vector<string> Client::getUsersRequests(){
	return usersRequests;
}

Client::~Client() {
}

} /* namespace gameClient */
