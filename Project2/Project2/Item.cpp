
#include "Item.h"

Item::Item() {
	setCountBorrow(0);
}
string Item::getName() {
	return name;
}
size_t Item::getCountBorrow() {
	return countBorrow;
}

vector<User*>& Item::getUsers() {
	return userData.getUsers();
}


void Item::setName(string newName) {
	name = newName;
}
void Item::setCountBorrow(size_t newCountBorrow) {
	countBorrow = newCountBorrow;
}

