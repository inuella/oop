#pragma once
#include "DVD.h"

DVD::DVD() {
	setCount(0);
}
string DVD::getMaker() {
	return maker;
}
size_t DVD::getCount() {
	return count;
}

void DVD::setMaker(string newMaker) {
	maker = newMaker;
}
void DVD::setCount(size_t newCount) {
	count = newCount;
}

bool DVD::Rent(User* user)
{
	if (getUsers().size() < getCount()) {
		getUsers().push_back(user);
		return true;
	}
	return false;
}

bool DVD::Return(User* user)
{
	vector<User*>::iterator it;
	for (it = getUsers().begin(); it != getUsers().end(); it++) {
		if (*it == user) {
			getUsers().erase(it);
			return true;
		}
	}
	return false;
}