#pragma once

#include "BookShop.h"
#include "DVDShop.h"
#include "Item.h"
#include "UserData.h"

class Librarian {
	
private:
	UserData userData;
		
public:
	Librarian();
	~Librarian();
	
	void Add(int num);

	void Find(int num);

	void Rent(int num);

	void Return(int num);

	void RentList();

	void List();

	void recoverAvailability();

	void FindUser();

	void UserList();

	void AddUser();
		
};