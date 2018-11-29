#pragma once

#include <string>
#include <vector>
#include "BookUser.h"

using namespace std;


class Book
{
	friend class BookShop;
private:
	string title;        // 도서 제목
	string publisher;    // 출판사
	size_t count;        // 전체 수량
	vector<BookUser*> users; // 대여 유저 목록

public:
	Book();
	// 도서 대여 처리.
	string getTitle();
	string getPublisher();
	size_t getCount();


	void setTitle(string newTitle);
	void setPublisher(string newPublisher);
	void setCount(size_t newCount);


	bool Rent(BookUser* user);
	// 도서 반납 처리.
	bool Return(BookUser* user);
	// 도서 정보 출력.
	friend ostream& operator<<(ostream& o, Book& book)
	{
		o << book.getTitle() << "\t" << book.getPublisher() << "\t";
		o << book.getCount() - book.users.size() << "/" << book.getCount() << "\t";
		return o;
	}
};