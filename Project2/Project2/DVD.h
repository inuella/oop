#pragma once
#pragma once

#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class DVD : public Item

{
	friend class DVDShop;
private:
	string maker;    // ���ǻ�
	size_t count;        // ��ü ����

public:
	DVD();
	string getMaker();
	size_t getCount();

	void setMaker(string newMaker);
	void setCount(size_t newCount);

	friend ostream& operator<<(ostream& o, DVD& dvd)
	{
		o << dvd.getName() << "\t" << dvd.getMaker() << "\t";
		o << dvd.getCount() - dvd.getUsers().size() << "/" << dvd.getCount() << "\t";
		return o;
	}

	 bool Rent(User* user);

     bool Return(User* user);
};