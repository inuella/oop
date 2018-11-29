#pragma once


#ifndef DVDUSER_H
#define DVDUSER_H

#include <fstream>
#include <iostream>
#include <string>
#include "User.h"



using namespace std;

class DVDUser : public User
{
	friend class DVDShop;
private:

public:
	DVDUser() { };


	// 유저 정보 출력.
	friend ostream& operator<<(ostream& o, DVDUser& user)
	{
		o << user.getName() << "\t" << user.getBirth() << "\t";
		o << user.getPhone() << "\t" << user.getAddress() << "\t" << user.getDueDate() << "\t" << user.getAvailability() << "\t";

		return o;
	}
};

#endif;