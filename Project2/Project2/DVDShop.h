#pragma once
#pragma once
// 도서 대여점 클래스.

#include <iostream>
#include <vector>
#include "DVD.h"
#include "Item.h"
#include "Shop.h"
#include "Librarian.h"
#include "UserData.h"

class DVDShop : public Shop
{
private:
	vector<DVD> m_dvds; 

	DVD* find_dvd(string title);

	UserData userData;

	User* find_user(string name);

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



};