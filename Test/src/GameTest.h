/*
 * GameTest.h
 *
 *  Created on: Sep 11, 2017
 *      Author: user
 */

#ifndef SRC_GAMETEST_H_
#define SRC_GAMETEST_H_

#include <iostream>
#include "MThread.h"
#include "UDPSocket.h"
#include "TheDogGame.h"

using namespace std;
using namespace networkingLab;
using namespace game;

class GameTest:MThread{
private:
	bool successful;
	TheDogGame* dog;
	UDPSocket* test;
public:
	GameTest();
	bool startTest();
	string readData();
	virtual void run();
	virtual ~GameTest();
};

#endif /* SRC_GAMETEST_H_ */
