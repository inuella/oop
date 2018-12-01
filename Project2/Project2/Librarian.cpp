
#include "Librarian.h"

BookShop bookshop;
DVDShop dvdshop;


Librarian::Librarian() {
	userData.readUserData();
}

Librarian::~Librarian() {
	userData.writeUserData();
}


void Librarian::Add(int num) {
	if (num == 1) {
		bookshop.Add();
	}
	else if (num == 2) {
		dvdshop.Add();
	}
}

void Librarian::Find(int num) {
	if (num == 1) {
		bookshop.Find();
	}
	else if (num == 2) {
		dvdshop.Find();
	}
}

void Librarian::Rent(int num) {
	if (num == 1) {
		bookshop.Rent();
	}
	else if (num == 2) {
		dvdshop.Rent();
	}
}

void Librarian::Return(int num) {
	if (num == 1) {
		bookshop.Return();
	}
	else if (num == 2) {
		dvdshop.Return();
	}
}

void Librarian::RentList() {
		bookshop.RentList();
		dvdshop.RentList();
}

void Librarian::List() {
		bookshop.List();
		dvdshop.List();
}

void Librarian ::FindUser()
{
	userData.FindUser();
}

void Librarian::UserList() {
	
	userData.UserList();
	
}

void Librarian::AddUser()
{
	userData.AddUser();
}

void Librarian::recoverAvailability() {

	userData.recoverAvailability();
}