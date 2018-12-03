#pragma once

#include "BookShop.h"
#include "DVDShop.h"
#include "MagazineShop.h"

class Librarian {
	
private:

	BookShop bookshop;
	DVDShop dvdshop;
	MagazineShop magazineshop;
		
public:
	Librarian();
	~Librarian();
	
	void Add(int num);

	void Find(int num);

	void Rent(int num);

	void Return(int num);

	void RentList();

	void List();

	void recoverAvailability(int num);

	void FindUser(int num);

	void UserList(int num);

	void AddUser(int num);
		
};