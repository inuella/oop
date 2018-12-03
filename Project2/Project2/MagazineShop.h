#pragma once

#include <fstream>
#include "Shop.h"
#include "Magazine.h"


class MagazineShop : public Shop {

private:
	vector<Magazine> m_magazines;
	vector<User> m_users;

	Magazine* find_magazine(string title);

#pragma once


public:

	MagazineShop();
	~MagazineShop();

	 bool compareTime(User* user);

	void Add();

	void Find();

	void Rent();

	void Return();

	void RentList();

	void List();

	void readUserData();

	void writeUserData();

	User* find_user(string name);

	void getList();

	void recoverAvailability();

	void FindUser();

	void UserList();

	void AddUser();
};