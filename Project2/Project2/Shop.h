#pragma once
#pragma once
// 도서 대여점 클래스.

#include <iostream>
#include <vector>

using namespace std;

class Shop
{

public:
	// 생성자 - 파일 읽기.

	Shop();
	~Shop();

	string timeCheck();

	// 도서 추가 함수.
	virtual void Add() = 0;

	string monthChange(string mon);

	// 도서 검색 함수.
	virtual void Find() = 0;

	// 도서 대여 함수.
	virtual void Rent() = 0;

	// 도서 반납 함수.
	virtual void Return() = 0;

	// 도서 대여 목록 출력 함수.
	virtual void RentList() = 0;

	virtual void List() = 0;

	virtual void recoverAvailability() = 0;
};