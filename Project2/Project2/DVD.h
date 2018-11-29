#pragma once
#pragma once

#include <string>
#include <vector>
#include "DVDUser.h"

using namespace std;

class DVD

{
	friend class DVDShop;
private:
	string title;        // ���� ����
	string maker;    // ���ǻ�
	size_t count;        // ��ü ����
	vector<DVDUser*> users; // �뿩 ���� ���

public:
	DVD();
	// ���� �뿩 ó��.
	string getTitle();
	string getMaker();
	size_t getCount();

	void setTitle(string newTitle);
	void setMaker(string newMaker);
	void setCount(size_t newCount);

	bool Rent(DVDUser* user);
	// ���� �ݳ� ó��.
	bool Return(DVDUser* user);
	// ���� ���� ���.
	friend ostream& operator<<(ostream& o, DVD& dvd)
	{
		o << dvd.getTitle() << "\t" << dvd.getMaker() << "\t";
		o << dvd.getCount() - dvd.users.size() << "/" << dvd.getCount() << "\t";
		return o;
	}
};