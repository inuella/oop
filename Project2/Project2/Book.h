#pragma once

#include <string>
#include <vector>
#include "User.h"

using namespace std;


class Book
{
	friend class BookShop;
private:
	string title;        // ���� ����
	string publisher;    // ���ǻ�
	size_t count;        // ��ü ����
	vector<User*> users; // �뿩 ���� ���

public:
	Book();
	// ���� �뿩 ó��.
	string getTitle();
	string getPublisher();
	size_t getCount();
	vector<User*> getUsers();

	void setTitle(string newTitle);
	void setPublisher(string newPublisher);
	void setCount(size_t newCount);
	void setUsers(vector<User*> newUsers);

	bool Rent(User* user);
	// ���� �ݳ� ó��.
	bool Return(User* user);
	// ���� ���� ���.
	friend ostream& operator<<(ostream& o, Book& book)
	{
		o << book.title << "\t" << book.publisher << "\t";
		o << book.count - book.users.size() << "/" << book.count << "\t";
		return o;
	}
};