#pragma once
// ���� �뿩�� Ŭ����.

#include <iostream>
#include <vector>
#include "Book.h"
#include "User.h"

class BookShop
{
private:
	vector<Book> m_books;      // ���� ���.
	vector<User> m_users;      // ���� ���.

	// ���� ã�� ���� �Լ�.
	User* find_user(string name);
	// ���� ã�� ���� �Լ�.
	Book* find_book(string title);


public:
	// ������ - ���� �б�.
	BookShop();
	~BookShop();

	// ���� �߰� �Լ�.
	void AddUser();
	// ���� ���� �Լ�.
	void DeleteUser();
	// ���� �߰� �Լ�.
	void AddBook();
	// ���� ���� �Լ�.
	void DeleteBook();

	// ���� �˻� �Լ�.
	void FindUser();

	// ���� �˻� �Լ�.
	void FindBook();

	// ���� �뿩 �Լ�.
	void RentBook();

	// ���� �ݳ� �Լ�.
	void ReturnBook();

	// ���� �뿩 ��� ��� �Լ�.
	void RentList();

	void BookList();

	void UserList();

};