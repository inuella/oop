#pragma once


#include <string>
#include <vector>
#include "User.h"
#include "UserData.h"


using namespace std;

class Item{

	friend class BookShop;
	friend class DVDShop;

private:
	string name;       
	size_t countBorrow;
	UserData userData;

public:
	Item();
	string getName();
	size_t getCountBorrow();
	vector<User*>& getUsers();

	void setName(string newName);
	void setCountBorrow(size_t newCountBorrow);

};