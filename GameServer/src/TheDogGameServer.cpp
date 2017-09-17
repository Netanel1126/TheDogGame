/*
 * TheHuntingGameServer.cpp
 *
 *  Created on: Aug 10, 2017
 *      Author: user
 */

#include "TheDogGameServer.h"
#include <string>
#include <sstream>

using namespace gameServer;
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////ClientHendler///////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

ClientHendler::ClientHendler(TCPSocket* socket, TheDogGameServer* server,
		string myUserName) {
	this->socket = socket;
	this->server = server;
	this->myUserName = myUserName;
	stop = false;
}

void ClientHendler::run() {
	int command;
	string buffer,msg = "";

	while (!stop) {
		command = readCommand(socket);
		msg = commandToString(command, myUserName);
		switch (command) {
		case getAllConnectedUsers:
			server->sendActiveUser(socket);
			break;

		case connectToUser:
			buffer = readData(socket);
			msg += buffer;
			server->sendConectionRequst(buffer, this);
			break;

		case refusedConnection:
			buffer = readData(socket);
			msg += buffer;
			server->refusedConection(myUserName, buffer);
			break;

		case acceptConnection:
			buffer = readData(socket);
			msg += buffer;
			server->conectToUser(buffer, this);
			break;

		case Kill:
			server->removeFromeActiveUsers(myUserName);
			stop = true;
			break;

		case addToScorebord:
			buffer = readData(socket);
			server->addToScoreBoard(buffer,readCommand(socket));
			break;

		case getScoreboard:
			server->sendScoreBoard(socket, myUserName);
			break;

		}
		cout<<msg<<endl;
	}
}


string ClientHendler::commandToString(int command,string userName){
	string msg = userName;
	msg += " Command: ";
	switch(command){

	case addToScorebord:
		msg += "addToScorebord";
		break;

	case getAllConnectedUsers:
		msg += "getAllConnectedUsers";
		break;

	case connectToUser:
		msg += "connectToUser ";
		break;

	case acceptConnection:
		msg += "acceptConnection ";
		break;

	case refusedConnection:
		msg += "refusedConnection ";
		break;

	case startGame:
		msg += "startGame";
		break;

	case getScoreboard:
		msg += "getScoreboard";
		break;

	case loadUser:
		msg += "loadUser";
		break;

	case newUser:
		msg += "newUser";
		break;

	case Kill:
		msg += "Kill";
		break;

	default:
		msg += "ERROR command not found";
		break;
	}

	return msg;
}

void ClientHendler::statThread() {
	this->start();
}

int ClientHendler::readCommand(TCPSocket* peer) {
	int command;
	// Read a command from socket
	peer->recv((char*) &command, 4);
	return ntohl(command);
}

string ClientHendler::readData(TCPSocket* peer) {
	// Read a string from socket
	int length = readCommand(peer);
	// Receive the incoming message
	char buffer[length];
	//memset((void*) buffer, 0, length);

	int rc = peer->recv(buffer, length);
	if (rc < 0) {
		perror("Error receiving socket");
		return "";
	}
	string str = buffer;
	return str.substr(0, length);
}

TCPSocket* ClientHendler::getSocket() {
	return this->socket;
}

string ClientHendler::getMyUserName() {
	return myUserName;
}

ClientHendler::~ClientHendler() {
	stop = true;
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////
//////////////////TheHuntingGameServer/////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

TheDogGameServer::TheDogGameServer() {
	readUsers();
	scoreBoard = readScoreBoard();
	TCPServer = new TCPSocket(1126);
	this->start();
}

bool TheDogGameServer::userExsist(User user) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].equals(user))
			return true;
	}
	return false;
}

void TheDogGameServer::AddUser(User user) {
	if (!userExsist(user))
		users.push_back(user);
}

void TheDogGameServer::writeUsers() {
	ofstream writeUsers;
	writeUsers.open("Users.txt");
	for (int i = 0; i < users.size(); i++) {
		int lengte = users[i].getUserName().length();
		writeUsers.write((char*) &lengte, 4);
		writeUsers.write(users[i].getUserName().data(), lengte);

		lengte = users[i].getPassword().length();
		writeUsers.write((char *) &lengte, 4);
		writeUsers.write(users[i].getPassword().data(), lengte);
	}
	writeUsers.close();
}

void TheDogGameServer::readUsers() {
	ifstream readUsers;
	readUsers.open("Users.txt", ios::in);
	string userName, password, temp;
	User user;
	int size;
	if (readUsers.is_open()) {
		while (readUsers.read((char *) &size, 4)) {
			char tempUserName[size];
			readUsers.read(tempUserName, size);
			temp = tempUserName;
			userName = temp.substr(0, size);

			readUsers.read((char *) &size, 4);
			char tempPassword[size];
			readUsers.read(tempPassword, size);
			temp = tempPassword;
			password = temp.substr(0, size);
			user.setUser(userName, password);
			users.push_back(user);
		}
		readUsers.close();
	}
}


void TheDogGameServer::writeScoreBoard(priority_queue<ScoreBoard,std::vector<ScoreBoard>,myComparison> pq){
	ofstream writeScoreBoard;
	writeScoreBoard.open("ScoreBoard.txt");
	while(!pq.empty()) {
		int lengte = pq.top().userName.length();
		writeScoreBoard.write((char*) &lengte, 4);
		writeScoreBoard.write(pq.top().userName.data(), lengte);

		writeScoreBoard.write((char *) &pq.top().score, 4);
		pq.pop();
	}
	writeScoreBoard.close();
}
priorityQueue TheDogGameServer::readScoreBoard(){
	priorityQueue pq;

	ifstream readScoreBoard;
	readScoreBoard.open("ScoreBoard.txt", ios::in);
	string userName;
	ScoreBoard sb;
	int size;
	if (readScoreBoard.is_open()) {
		while (readScoreBoard.read((char *) &size, 4)) {
			char tempUserName[size];
			readScoreBoard.read(tempUserName, size);
			userName = tempUserName;
			sb.userName = userName.substr(0, size);

			readScoreBoard.read((char *) &size, 4);
			sb.score = size;
			pq.push(sb);
		}
		readScoreBoard.close();
	}
	return pq;
}
void TheDogGameServer::sendScoreBoard(TCPSocket* socket,string userName){
	string scoreboard = "Scoreboard\n";
	priorityQueue pq = scoreBoard;

	while(!pq.empty()){
		ostringstream o;
		scoreboard += pq.top().userName;
		scoreboard +=" Score: ";
		o<<pq.top().score;
		scoreboard += o.str();
		scoreboard += "\n";
		pq.pop();
	}
	sendCommand(socket, getScoreboard);
	sendMsgToClient(socket, scoreboard);
}

void TheDogGameServer::addToScoreBoard(string userName,int score){
	ScoreBoard sb;
	sb.score = score;
	sb.userName = userName;
	scoreBoard.push(sb);
}


void TheDogGameServer::close() {
	stop = true;
	this->stopThread();
	writeUsers();
	writeScoreBoard(scoreBoard);
	TCPServer->close();
}

TheDogGameServer::~TheDogGameServer() {
}

void TheDogGameServer::addActiveUser(string userName,
		ClientHendler* hendler) {
	activeUsers[userName] = hendler;
}

void TheDogGameServer::sendActiveUser(TCPSocket* socket) {
	string activeUsersList = "Active Users\n";
	sendCommand(socket, getAllConnectedUsers);
	for (std::map<string, ClientHendler*>::const_iterator i =
			this->activeUsers.begin(); i != this->activeUsers.end(); i++) {
		string temp = i->first;
		activeUsersList += temp;
		activeUsersList += "\n";
	}
	sendMsgToClient(socket, activeUsersList);
}

void TheDogGameServer::conectToUser(string userName, ClientHendler* user) {
	TCPSocket* userSocket = user->getSocket();
	int command,port1,port2;
	string msg;
	srand (time(NULL));

	if(activeUsers.find(userName) == activeUsers.end()){
		msg = "ERROR - User doesn't exist";
		sendMsgToClient(userSocket, msg);
		return;
	}
	TCPSocket* userToSend = activeUsers[userName]->getSocket();
	command = startGame;
	sendCommand(userSocket, command);
	sendCommand(userToSend, command);
	//user->readCommand(userSocket);
	//user->readCommand(userToSend);

	port1 = rand() % 100 + 9901;
	port2 = rand() % 100 + 9901;

	msg = userToSend->getAddr();
	sendMsgToClient(userSocket, msg);
	sendMsgToClient(userSocket, userName);
	sendCommand(userSocket, port1);//send's his port for udp
	sendCommand(userSocket, port2);//send's player 2 port

	msg = userSocket->getAddr();
	sendMsgToClient(userToSend, msg);
	sendMsgToClient(userToSend,user->getMyUserName());
	sendCommand(userToSend, port2);//send's his port for is udp
	sendCommand(userToSend, port1);//send's player 1 port
}

void TheDogGameServer::sendConectionRequst(string userName, ClientHendler* user){
	TCPSocket* userSocket = user->getSocket();
	int command, temp;
	string msg;

	if(activeUsers.find(userName) == activeUsers.end()){
		msg = "ERROR - User doesn't exist";
		cout<<userName<<" "<<msg;
		sendMsgToClient(userSocket, msg);
		return;
	}

	TCPSocket* userToSend = activeUsers[userName]->getSocket();
	command = connectToUser;
	//send user connection request and the user that requested the connection
	sendCommand(userToSend, command);

	msg = user->getMyUserName();
	sendMsgToClient(userToSend, msg);
}

void TheDogGameServer::refusedConection(string myUserName,string toSend){
	TCPSocket* userSocket = activeUsers[toSend]->getSocket();
	string msg = myUserName;
	msg += " Refused Connection";
	sendCommand(userSocket, refusedConnection);
	sendMsgToClient(userSocket, msg);
}

void TheDogGameServer::removeFromeActiveUsers(string userName) {
	activeUsers.erase(userName);
}

void TheDogGameServer::run() {

	string msg;
	ClientHendler* c;

	while (!stop) {
		User user;
		int command;
		TCPSocket* accapt = TCPServer->listenAndAccept();
		if (accapt != NULL) {
			//get userName and password
			command = c->readCommand(accapt);
			user = getUser(accapt);

			if (command == loadUser) {
				for (int i = 0; i < 2; i++) {
					if (userExsist(user))
						break;
					else {
						msg = "User doesn't exist please try again";
						sendMsgToClient(accapt, msg);
						c->readCommand(accapt);
						user = getUser(accapt);
					}
				}
				if (!userExsist(user)) {
					sendMsgToClient(accapt, "Kill");
				} else
					sendWelcomeBackMsg(accapt, user.getUserName());

			} else if (command == newUser) {
				while (command != Kill) {
					if (userExsist(user)) {
						msg = "User Exists Try again";
						sendMsgToClient(accapt, msg);
						user = getUser(accapt);
					} else{
						msg = "Welcome ";
						msg += user.getUserName();
						sendMsgToClient(accapt, msg);
						AddUser(user);
						break;
					}
					command = c->readCommand(accapt);
				}
			}

			if (command != Kill) {
				c = new ClientHendler(accapt, this, user.getUserName());
				addActiveUser(user.getUserName(), c);
				c->statThread();
			}
		}

		else {
			sleep(60);
		}
	}
}

void TheDogGameServer::sendWelcomeBackMsg(TCPSocket* peer,
		string userName) {
	string msg;
	msg = "Welcome Back ";
	msg += userName;
	sendMsgToClient(peer, msg);
}

User TheDogGameServer::getUser(TCPSocket* peer) {
	string userName, password;
	ClientHendler* c;
	User user;

	userName = c->readData(peer);
	password = c->readData(peer);
	user.setUser(userName, password);
	return user;
}

void TheDogGameServer::sendCommand(TCPSocket* peer, int command) {
	int msgLen = htonl(command);
	peer->send((char*) &msgLen, 4);
}

void TheDogGameServer::sendMsgToClient(TCPSocket* peer, string msg) {
	int msgLen = htonl(msg.length());
	peer->send((char*) &msgLen, 4);
	peer->send(msg.data(), msg.length());
}

/////////////////////////Get & Set/////////////////////////////////////////
const map<string, ClientHendler*>& TheDogGameServer::getActiveUsers() const {
	return activeUsers;
}

vector<User>& TheDogGameServer::getUsers() {
	return users;
}

void TheDogGameServer::setUsers(const vector<User>& users) {
	this->users = users;
}

