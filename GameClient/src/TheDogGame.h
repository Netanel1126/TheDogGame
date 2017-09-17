/*
 * TheHuntingGame.h
 *
 *  Created on: Aug 18, 2017
 *      Author: user
 */

#ifndef SRC_THEDOGGAME_H_
#define SRC_THEDOGGAME_H_

#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include "MThread.h"
#include "UDPSocket.h"

using namespace std;
using namespace networkingLab;

namespace game{
class TheDogGame:MThread{
public:
	struct Player{
		string playerName;
		UDPSocket* playerSocket;
		string ip;
		int port;
		int score = 0;
	};
private:
	bool stop;
	string backyard[11];
	string player2_backyard[11];
	Player player1,player2;
	string buffer;
public:
	TheDogGame(string player1_ip,string player1_UserName,int player1_port,
			string player2_ip,string player2_UserName,int player2_port);
	void about();
	void play();
	bool enterGameBoard(string backyard[11],string location,string location1,char toSerch,char replace);
	vector<string> split(string toSplit, char splitBy);
	int starGame();//returns score
	void initGameBoard();
	void printGameBoard(string gameBoard[11]);

	string readData();
	void sendData(string msg);

	virtual void run();
	void close();
	virtual ~TheDogGame();
};
}

#endif /* SRC_THEDOGGAME_H_ */
