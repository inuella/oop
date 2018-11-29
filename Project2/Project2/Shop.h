#pragma once
#pragma once
// ���� �뿩�� Ŭ����.

#include <iostream>
#include <vector>

using namespace std;

class Shop
{

public:
	// ������ - ���� �б�.

	Shop();
	~Shop();

	string timeCheck();

	// ���� �߰� �Լ�.
	virtual void Add() = 0;

	string monthChange(string mon);

	// ���� �˻� �Լ�.
	virtual void Find() = 0;

	// ���� �뿩 �Լ�.
	virtual void Rent() = 0;

	// ���� �ݳ� �Լ�.
	virtual void Return() = 0;

	// ���� �뿩 ��� ��� �Լ�.
	virtual void RentList() = 0;

	virtual void List() = 0;

	virtual void recoverAvailability() = 0;
};