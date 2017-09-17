/*
 * test.cpp
 *
 *  Created on: Sep 12, 2017
 *      Author: user
 */

#include "ServerTest.h"
#include "TheDogGameServer.h"
#include "GameTest.h"
#include "ClientTest.h"

int main(){
	//Server Test
	/*ServerTest *s = new ServerTest;
	if(s->startTest())
		cout<<"Server TEST was successful"<<endl;
	else
		cout<<"Server TEST Failed"<<endl;
	delete s;*/

	ClientTest* c = new ClientTest;
	if(c->startTest())
		cout<<"Client TEST was successful"<<endl;
	else
		cout<<"Client TEST Failed"<<endl;
	delete c;

	/*GameTest* g = new GameTest;
	if(g->startTest())
		cout<<"Game TEST was successful"<<endl;
	else
		cout<<"Game TEST Failed"<<endl;
	delete g;*/
}

