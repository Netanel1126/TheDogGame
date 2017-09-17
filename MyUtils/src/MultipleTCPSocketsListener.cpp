

#include "MultipleTCPSocketsListener.h"

using namespace std;
using namespace networkingLab;

/*
 * Add the given socket to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSocket(TCPSocket* socket){
	this->vSocket.push_back(socket);
}

/*
 * Set the given sockets to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSockets(vector<TCPSocket*> socketVec){
	//TODO: set the given sockets as the socket list to selct from
	vSocket.insert(vSocket.end(),socketVec.begin() ,socketVec.end());
}

/*
 * This method checks to see if any of the previous given sockets are ready for reading
 * It returns one of the Sockets that are ready.
 */
TCPSocket* MultipleTCPSocketsListener::listenToSocket(){
	fd_set readfd;
	FD_ZERO(&readfd);
	struct timeval timeval;

	timeval.tv_sec = 1;
	timeval.tv_usec = 0;
	int numfds = 0;

	//fill the set with file descriptors from the socket list using (FD_SET macro)
	for (int i = 0; i < vSocket.size();i++){
		FD_SET(vSocket[i]->sock,&readfd);
		if(numfds < vSocket[i]->sock)
			numfds = vSocket[i]->sock;
	}
	//perform the select
	 int numOf_select = ::select(numfds + 1, &readfd, NULL, NULL, &timeval);

	//check the returned value from the select to find the socket that is ready
	 if(numOf_select < 0){
		 cout<<"ERROR in select socket"<<endl;
		 return NULL;
	 }
	 else if (numOf_select == 0) {
		 cout<<"ERROR - Nobody is Ready"<<endl;
		 return NULL;
	}
	//if select return a valid socket return the matching TCPSocket object otherwise return NULL
	 for (int i = 0; i < vSocket.size(); i++) {
		 TCPSocket* tcpSock = vSocket[i];
		 if(FD_ISSET(vSocket[i]->getSock(),&readfd)){
			 return tcpSock;
		 }
	}
	return NULL;
}

