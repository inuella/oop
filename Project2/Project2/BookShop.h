#pragma once
// 도서 대여점 클래스.

#include <fstream>
#include "Shop.h"
#include "Book.h"

class BookShop : public Shop
{

private:
	vector<Book> m_books;   
	vector<User> m_users;

	Book* find_book(string title);

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

	 void readUserData();

	 void writeUserData();

	 User* find_user(string name);

	 void getList();

	 void recoverAvailability();

	 void FindUser();

	 void UserList();

	 void AddUser();
};