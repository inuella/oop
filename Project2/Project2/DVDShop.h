#pragma once
#pragma once
// ���� �뿩�� Ŭ����.

#include <iostream>
#include <vector>
#include "DVD.h"
#include "DVDUser.h"
#include "Shop.h"

class DVDShop : public Shop
{
private:
	vector<DVD> m_dvds;      // ���� ���.
	vector<DVDUser> m_users;      // ���� ���.

	// ���� ã�� ���� �Լ�.
	DVDUser* find_user(string name);
	// ���� ã�� ���� �Լ�.
	DVD* find_dvd(string title);


public:
	// ������ - ���� �б�.
	DVDShop();
	~DVDShop();

	// ���� �߰� �Լ�.
	void AddUser();
	// ���� �߰� �Լ�.
	void Add();

	bool compareTime(DVDUser* user);


	// ���� �˻� �Լ�.
	void FindUser();

	// ���� �˻� �Լ�.
	void Find();

	// ���� �뿩 �Լ�.
	void Rent();

	// ���� �ݳ� �Լ�.
	void Return();

	// ���� �뿩 ��� ��� �Լ�.
	void RentList();

	void List();

	void UserList();

	void recoverAvailability();

};