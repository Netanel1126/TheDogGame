/*
 * TheHuntingGame.cpp
 *
 *  Created on: Aug 18, 2017
 *      Author: user
 */

#include "TheDogGame.h"

namespace game{
TheDogGame::TheDogGame(string player1_ip,string player1_UserName,int player1_port,
		string player2_ip,string player2_UserName,int player2_port) {

	player1.ip = player1_ip;
	player1.port = player1_port;
	player1.playerName = player1_UserName;
	player1.playerSocket = new UDPSocket(player1.port);

	player2.ip = player2_ip;
	player2.port = player2_port;
	player2.playerName = player2_UserName;

	stop = false;
	initGameBoard();
}

void TheDogGame::initGameBoard() {
	backyard[0] = "------------";
	backyard[1] = " |1|2|3|4|5|";
	backyard[2] = "-|-|-|-|-|-|";
	backyard[3] = "A| | | | | |";
	backyard[4] = "-|-|-|-|-|-|";
	backyard[5] = "B| | | | | |";
	backyard[6] = "-|-|-|-|-|-|";
	backyard[7] = "C| | | | | |";
	backyard[8] = "-|-|-|-|-|-|";
	backyard[9] = "D| | | | | |";
	backyard[10] = "------------";

	for (int i = 0; i < 11; ++i) {
		player2_backyard[i] = backyard[i];
	}
}

bool TheDogGame::enterGameBoard(string backyerd[11],string location,string location1,
		char toSearch,char replace){
	int place,place1;
	if(location == "A")
		place = 3;
	else if(location == "B")
		place = 5;
	else if(location == "C")
		place = 7;
	else if(location == "D")
		place = 9;
	else
		return false;

	if(location1 == "1")
		place1 = 2;
	else if(location1 == "2")
		place1 = 4;
	else if(location1 == "3")
		place1 = 6;
	else if(location1 == "4")
		place1 = 8;
	else if(location1 == "5")
		place1 = 10;
	else
		return false;

	if(backyard[place][place1] == toSearch){
		backyard[place][place1] = replace;
		return true;
	}
	else
		return false;

}

vector<string> TheDogGame::split(string toSplit, char splitBy) {
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

int TheDogGame::starGame(){
	string location,location1;
	cout<<"Welcome to The Dog game!!!\n"
			"Would you like to read the about enter 'y' if yes"<<endl;
	cin>>location;
	if(location == "y")
		about();

	for (int i = 0; i < 5; ++i) {
		cout<<"please choose where you would like to bury your "<<i+1<<" bone in this map"<<endl;
		printGameBoard(backyard);
		cin>>location>>location1;
		if(!enterGameBoard(backyard,location,location1,' ','O')){
			cout<<"ERROR - Please try again"<<endl;
			i--;
		}
	}
	this->start();
	this->play();

	sendData("Finished");
	cout<<"Waiting for user..."<<endl;

	while(buffer != "Finished"){sleep(5);}
	if(player1.score > player2.score)
		cout<<"WIN!!!"<<endl;
	else if(player1.score < player2.score)
		cout<<"Lose"<<endl;
	else
		cout<<"Tie"<<endl;
	this->close();
	return player1.score;
}

void TheDogGame::run() {
	string buffer1;
	vector<string> commands;
	while(!stop){
		buffer = readData();
		if(buffer == "Dig"){
			buffer1 = readData();
			commands = split(buffer1, ' ');
			if(enterGameBoard(backyard,commands[0], commands[1], 'O', 'X')){
				sendData("Fond");
				player2.score += 100;
			}else
				sendData("NotFond");
			sendData(buffer1);
		}

		else if(buffer == "Fond"){
			commands = split(readData(), ' ');
			enterGameBoard(player2_backyard,commands[0], commands[1],' ', 'O');
			player1.score += 100;
		}

		else if(buffer == "NotFond"){
			commands = split(readData(), ' ');
			enterGameBoard(player2_backyard,commands[0], commands[1],' ', 'X');
		}else if(buffer == "Finished"){break;}
		else
			cout<<"ERROR - Command not found"<<endl;
	}
}

void TheDogGame::play() {
	string buffer,msg;
	for (int i = 0; i < 10; ++i) {

		if(player1.score == 500){
			cout<<"Congratulations you found all 5 bones"<<endl;
			break;
		}
		cout<<"What would you like to do\n"
				"Enter 'm' to show your backyard\n"
				"Enter 'n' to show neighbor backyard\n"
				"Enter 'd' to dig in your neighbor backyard\n"
				"Enter 'a' for about"<< endl;
		cin>>buffer;

		if(buffer == "m")
			printGameBoard(backyard);
		else if(buffer == "n")
			printGameBoard(player2_backyard);
		else if(buffer == "d"){
			sendData("Dig");
			cout<<"Where would you like to dig"<<endl;
			cin>>buffer;
			msg = buffer;
			msg += " ";
			cin>>buffer;
			msg += buffer;
			sendData(msg);

		}else if(buffer == "a")
			about();
		else{
			cout<<"ERROR - Command not found please try again"<<endl;
			i--;
		}
	}
}

void TheDogGame::sendData(string msg){
	player1.playerSocket->sendTo(msg, player2.ip, player2.port);
}

string TheDogGame::readData(){
	char buffer[100];
	memset((void*) buffer, 0, 100);

	player1.playerSocket->recv(buffer,100);
	return buffer;
}

void TheDogGame::printGameBoard(string gameBoard[11]){
	for (int i = 0; i < 11; ++i) {
		cout<<gameBoard[i]<<endl;
	}
}


void TheDogGame::about() {
	string msg = "The Dog Game is a turn based puzzle game for two players,\n"
	"\nHow To Play:\n"
	"Both players must first bury their 5 'bones' in the Backyard  by choosing the locations on the map\n"
	"the 'bones' will by marked wit 'O' then the players will have 10 chances to 'dig' the other player bones\n"
	"if player finds a 'bone' it will be marked with a 'O' and in the other player 'backyard' and your score will\n"
	"rise by 100 else it will be marked with 'X' if player finds a 'bone' in your 'backyard' it with 'X'\n"
	"Have fun!!!:)\n";

	cout<<msg<<endl;
}

void TheDogGame::close(){
	this->stop = true;
	this->stopThread();
	this->player1.playerSocket->close();
}

TheDogGame::~TheDogGame() {
}
}
