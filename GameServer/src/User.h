/*
 * User.h
 *
 *  Created on: Aug 10, 2017
 *      Author: user
 */

#ifndef SRC_USER_H_
#define SRC_USER_H_

#include <iostream>
#include <string>

using namespace std;
class User {
private:
	string userName;
	string password;
public:
	User();
	void setUser(string userName,string password);
	bool equals(User user);
	string getUserName();
	string getPassword();
	void setUserName(string userName);
	void setPassword(string password);

	virtual ~User();
};

#endif /* SRC_USER_H_ */
