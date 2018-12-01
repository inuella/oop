#pragma once
// ���� �뿩�� Ŭ����.

#include <iostream>
#include <vector>
#include "Book.h"
#include "Item.h"
#include "Shop.h"
#include "UserData.h"

class BookShop : public Shop
{
private:
	vector<Book> m_books;      // ���� ���.

	Book* find_book(string title);

	UserData userData;

	User* find_user(string name);

	#pragma once


public:

	BookShop();
	~BookShop();


	 void Add();

	bool compareTime(User* user);

	 void Find();

	void Rent();

	void Return();

	 void RentList();

	 void List();

};