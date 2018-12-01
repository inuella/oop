#pragma once
#include "Book.h"

Book::Book() {
	setCount(0);
}

string Book::getPublisher() {
	return publisher;
}
size_t Book::getCount() {
	return count;
}

void Book::setPublisher(string newPublisher) {
	publisher = newPublisher;
}
void Book::setCount(size_t newCount) {
	count = newCount;
}

bool Book::Rent(User* user)
{
	if (getUsers().size() < getCount()) {
		getUsers().push_back(user);
		return true;
	}
	return false;
}

bool Book::Return(User* user)
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