#pragma once

#include "Item.h"
#include "User.h"


class Book:public Item
{
	friend class BookShop;
private:
	string publisher;    // √‚∆«ªÁ
	size_t count;


public:
	Book();

	vector<User*> users;

	string getPublisher();
	size_t getCount();

	void setPublisher(string newPublisher);
	void setCount(size_t newCount);

	friend ostream& operator<<(ostream& o, Book& book)
	{
		o << book.getName() << "\t" << book.getPublisher() << "\t";
		o << book.getCount() - book.users.size() << "/" << book.getCount() << "\t";
		return o;
	}
	bool Rent(User* user);

	bool Return(User* user);
};