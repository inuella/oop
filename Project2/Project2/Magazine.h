#pragma once

#include "Item.h"

class Magazine : public Item
{
private:
	string ho;
	size_t count;


public:

	vector<User*> users;

	string getHo();

	void setHo(string newHo);

	size_t getCount();

	void setCount(size_t newCount);

	friend ostream& operator<<(ostream& o, Magazine& magazine)
	{
		o << magazine.getName() << "\t" << magazine.getHo() << "\t";
		o << magazine.getCount() - magazine.users.size() << "/" << magazine.getCount() << "\t";
		return o;
	}

	bool Rent(User* user);

	bool Return(User* user);
};