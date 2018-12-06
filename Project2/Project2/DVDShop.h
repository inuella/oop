#pragma once
#pragma once
// 도서 대여점 클래스.

#include <fstream>
#include "Shop.h"
#include "DVD.h"

class DVDShop : public Shop
{
private:
	vector<DVD> m_dvds; 
	vector<User> m_users;

	DVD* find_dvd(string title);

public:
	DVDShop();
	~DVDShop();

	void Add();

 	bool compareTime(User* user);

	void Find();

	void Rent();

	void Return();

	void RentList();

	void List();

	void readUserData();

	void writeUserData();

	User* find_user(string name, string birth, string number);

	User* find_user(string name);

	void getList();

	void recoverAvailability();

	void FindUser();

	void UserList();

	void AddUser();

};