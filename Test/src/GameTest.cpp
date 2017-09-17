/*
 * GameTest.cpp
 *
 *  Created on: Sep 11, 2017
 *      Author: user
 */

#include "GameTest.h"

GameTest::GameTest() {
	successful = false;
	dog = new TheDogGame("127.0.0.1","dog1",1126,"127.0.0.1","dog2",1127);
	test = new UDPSocket(1127);
}

bool GameTest::startTest(){
	//start a game enter : A 1 A 2 A 3 A 4 A 5 d A 3 d D 2 d D 2 d D 2 d D 2 n

	this->start();
	int result = dog->starGame();

	if(!successful)
		return false;

	if(result != 500)
		return false;

	return true;
}

string GameTest::readData(){
	char buffer[100];
	memset((void*) buffer, 0, 100);

	test->recv(buffer,100);
	return buffer;
}

void GameTest::run(){
	successful = false;
	string buffer;

	//sleep(5);
	buffer = readData();
	cout<<"1Game Buffer: "<<buffer<<endl;
	if(strcmp(buffer.data(), "Dig"))
		return;

	buffer = readData();
	cout<<"2Game Buffer: "<<buffer<<endl;
	if(strcmp(buffer.data(),"A 3"))
		return;

	//udp send fond A 3
	test->sendTo("Found", "127.0.0.1", 1126);
	test->sendTo("A 3", "127.0.0.1", 1126);

	//udp send dig A 3 and dig A 4
	test->sendTo("Dig", "127.0.0.1", 1126);
	test->sendTo("A 3", "127.0.0.1", 1126);

	buffer = readData();
	cout<<"3Game Buffer: "<<buffer<<endl;
	if(strcmp(buffer.data(),"Fond"))
		return;

	buffer = readData();
	cout<<"4Game Buffer: "<<buffer<<endl;
	if(strcmp(buffer.data(),"A 3"))
		return;

	test->sendTo("Dig", "127.0.0.1", 1126);
	test->sendTo("A 4", "127.0.0.1", 1126);

	buffer = readData();
	cout<<"5Game Buffer: "<<buffer<<endl;
	if(strcmp(buffer.data(),"Found"))
		return;

	buffer = readData();
	cout<<"6Game Buffer: "<<buffer<<endl;
	if(strcmp(buffer.data(),"A 4"))
		return;

	//udp sends dig C 1
	test->sendTo("Dig", "127.0.0.1", 1126);
	test->sendTo("C 1", "127.0.0.1", 1126);

	buffer = readData();
	cout<<"7Game Buffer: "<<buffer<<endl;
	if(strcmp(buffer.data(),"NotFound"))
		return;

	buffer = readData();
	cout<<"8Game Buffer: "<<buffer<<endl;
	if(strcmp(buffer.data(),"C 1"))
		return;

	//game will send dig D 2, 4 times and will get NotFond
	for (int i = 0;  i < 4; ++ i) {
		buffer = readData();
		cout<<"Game Buffer "<<i<<": "<<buffer<<endl;
		if(strcmp(buffer.data(),"Dig"))
			return;
		buffer = readData();
		cout<<"Game Buffer "<<i<<": "<<buffer<<endl;
		if(strcmp(buffer.data(),"D 2"))
			return;
		test->sendTo("NotFound", "127.0.0.1", 1126);
		test->sendTo("D 2", "127.0.0.1", 1126);
	}

	//game will receive Fond 4 times and will finish the game
	test->sendTo("Found", "127.0.0.1", 1126);
	test->sendTo("D 1", "127.0.0.1", 1126);
	test->sendTo("Found", "127.0.0.1", 1126);
	test->sendTo("D 3", "127.0.0.1", 1126);
	test->sendTo("Found", "127.0.0.1", 1126);
	test->sendTo("D 4", "127.0.0.1", 1126);
	test->sendTo("Found", "127.0.0.1", 1126);
	test->sendTo("D 5", "127.0.0.1", 1126);

	successful = true;
}

GameTest::~GameTest() {
	// TODO Auto-generated destructor stub
}

