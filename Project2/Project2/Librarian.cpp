
#include "Librarian.h"


Librarian::Librarian() {
}

Librarian::~Librarian() {
}




void Librarian::Add(int num) {
	if (num == 1) {
		bookshop.Add();
	}
	else if (num == 2) {
		dvdshop.Add();
	}
	else if (num == 3) {
		magazineshop.Add();
	}
}

void Librarian::Find(int num) {
	if (num == 1) {
		bookshop.Find();
	}
	else if (num == 2) {
		dvdshop.Find();
	}
	else if (num == 3) {
		magazineshop.Find();
	}
 }

void Librarian::Rent(int num) {
	if (num == 1) {
		bookshop.Rent();
	}
	else if (num == 2) {
		dvdshop.Rent();
	}
	else if (num == 3) {
		magazineshop.Rent();
	}
}

void Librarian::Return(int num) {
	if (num == 1) {
		bookshop.Return();
	}
	else if (num == 2) {
		dvdshop.Return();
	}
	else if (num == 3) {
		magazineshop.Return();
	}
}

void Librarian::RentList() {
		bookshop.RentList();
		dvdshop.RentList();
		magazineshop.RentList();
}

void Librarian::List() {
		bookshop.List();
		dvdshop.List();
		magazineshop.List();
}

void Librarian ::FindUser(int num)
{
	if (num == 1) {
		bookshop.FindUser();
	}
	else if (num == 2) {
		dvdshop.FindUser();
	}
	else if (num == 3) {
		magazineshop.FindUser();
	}
}

void Librarian::UserList(int num) {
	
	if (num == 1) {
		bookshop.UserList();
	}
	else if (num == 2) {
		dvdshop.UserList();
	}
	else if (num == 3) {
		magazineshop.UserList();
	}
	
}

void Librarian::AddUser(int num)
{
	if (num == 1) {
		bookshop.AddUser();
	}
	else if (num == 2) {
		dvdshop.AddUser();
	}
	else if (num == 3) {
		magazineshop.AddUser();
	}

}

void Librarian::recoverAvailability(int num) {

	if (num == 1) {
		bookshop.recoverAvailability();
	}
	else if (num == 2) {
		dvdshop.recoverAvailability();
	}
	else if (num == 3) {
		magazineshop.recoverAvailability();
	}
}
