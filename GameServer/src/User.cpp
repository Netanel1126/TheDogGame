/*
 * User.cpp
 *
 *  Created on: Aug 10, 2017
 *      Author: user
 */

#include "User.h"

User::User() {
	userName = "Default UserName";
	password ="Default Password";
}

void User::setUser(string userName,string password){
	this->userName = userName;
	this->password = password;
}

bool User::equals(User user){
	if(this->userName == user.getUserName() && this->password == user.getPassword())
		return true;
	return false;
}

string User::getUserName(){
	return userName;
}

string User::getPassword(){
	return password;
}

void User::setUserName(string userName){
	this->userName = userName;
}

void User::setPassword(string password){
	this->password = password;
}

User::~User() {}

