#pragma once
#pragma once


#ifndef BookUSER_H
#define BookUSER_H

#include <fstream>
#include <iostream>
#include <string>
#include "User.h"



using namespace std;

class BookUser : public User
{
	friend class BookShop;

public:
	BookUser() { };


	// 유저 정보 출력.
	friend ostream& operator<<(ostream& o, BookUser& user)
	{
		o << user.getName() << "\t" << user.getBirth() << "\t";
		o << user.getPhone() << "\t" << user.getAddress() << "\t" << user.getDueDate() << "\t" << user.getAvailability() << "\t";

		return o;
	}
};

#endif;