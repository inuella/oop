#pragma once
// 도서 대여점 클래스.

#include <iostream>
#include <vector>
#include "Book.h"
#include "User.h"

class BookShop
{
private:
	vector<Book> m_books;      // 도서 목록.
	vector<User> m_users;      // 유저 목록.

	// 유저 찾기 내부 함수.
	User* find_user(string name);
	// 도서 찾기 내부 함수.
	Book* find_book(string title);


public:
	// 생성자 - 파일 읽기.
	BookShop();
	~BookShop();

	// 유저 추가 함수.
	void AddUser();
	// 유저 삭제 함수.
	void DeleteUser();
	// 도서 추가 함수.
	void AddBook();
	// 도서 삭제 함수.
	void DeleteBook();

	// 유저 검색 함수.
	void FindUser();

	// 도서 검색 함수.
	void FindBook();

	// 도서 대여 함수.
	void RentBook();

	// 도서 반납 함수.
	void ReturnBook();

	// 도서 대여 목록 출력 함수.
	void RentList();

	void BookList();

	void UserList();

};