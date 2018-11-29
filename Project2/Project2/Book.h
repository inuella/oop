#pragma once

#include <string>
#include <vector>
#include "BookUser.h"

using namespace std;


class Book
{
	friend class BookShop;
private:
	string title;        // ���� ����
	string publisher;    // ���ǻ�
	size_t count;        // ��ü ����
	vector<BookUser*> users; // �뿩 ���� ���

public:
	Book();
	// ���� �뿩 ó��.
	string getTitle();
	string getPublisher();
	size_t getCount();


	void setTitle(string newTitle);
	void setPublisher(string newPublisher);
	void setCount(size_t newCount);


	bool Rent(BookUser* user);
	// ���� �ݳ� ó��.
	bool Return(BookUser* user);
	// ���� ���� ���.
	friend ostream& operator<<(ostream& o, Book& book)
	{
		o << book.getTitle() << "\t" << book.getPublisher() << "\t";
		o << book.getCount() - book.users.size() << "/" << book.getCount() << "\t";
		return o;
	}
};