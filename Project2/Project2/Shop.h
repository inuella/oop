#pragma once
#pragma once
// 도서 대여점 클래스.

#include <iostream>
#include <vector>
#include "User.h"

using namespace std;

class Shop
{

private:

public:

	Shop();
	~Shop();


	string timeCheck();

	// 도서 추가 함수.
	virtual void Add() = 0;

	string monthChange(string mon);


	virtual void Find() = 0;

	virtual void Rent() = 0;

	virtual void Return() = 0;

	virtual void RentList() = 0;

	virtual void List() = 0;

	virtual void getList() = 0;

	virtual void recoverAvailability() = 0;

	virtual void FindUser() = 0;

	virtual void UserList() = 0;

	virtual void AddUser() = 0;

};