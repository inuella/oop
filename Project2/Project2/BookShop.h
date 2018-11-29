#pragma once
// 도서 대여점 클래스.

#include <iostream>
#include <vector>
#include "Book.h"
#include "BookUser.h"
#include "Shop.h"

class BookShop : public Shop
{
private:
	vector<Book> m_books;      // 도서 목록.
	vector<BookUser> m_users;      // 유저 목록.

	// 유저 찾기 내부 함수.
	BookUser* find_user(string name);
	// 도서 찾기 내부 함수.
	Book* find_book(string title);

	#pragma once


public:
	// 생성자 - 파일 읽기.
	BookShop();
	~BookShop();

	// 유저 추가 함수.
	void AddUser();
	// 도서 추가 함수.
	 void Add();

	bool compareTime(BookUser* user);

	// 유저 검색 함수.
	void FindUser();

	// 도서 검색 함수.
	 void Find();

	// 도서 대여 함수.
	void Rent();

	// 도서 반납 함수.
	void Return();

	// 도서 대여 목록 출력 함수.
	 void RentList();

	 void List();

	void UserList();

	void recoverAvailability();

};