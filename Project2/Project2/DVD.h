#pragma once
#pragma once

#include <string>
#include <vector>
#include "DVDUser.h"

using namespace std;

class DVD

{
	friend class DVDShop;
private:
	string title;        // 도서 제목
	string maker;    // 출판사
	size_t count;        // 전체 수량
	vector<DVDUser*> users; // 대여 유저 목록

public:
	DVD();
	// 도서 대여 처리.
	string getTitle();
	string getMaker();
	size_t getCount();

	void setTitle(string newTitle);
	void setMaker(string newMaker);
	void setCount(size_t newCount);

	bool Rent(DVDUser* user);
	// 도서 반납 처리.
	bool Return(DVDUser* user);
	// 도서 정보 출력.
	friend ostream& operator<<(ostream& o, DVD& dvd)
	{
		o << dvd.getTitle() << "\t" << dvd.getMaker() << "\t";
		o << dvd.getCount() - dvd.users.size() << "/" << dvd.getCount() << "\t";
		return o;
	}
};