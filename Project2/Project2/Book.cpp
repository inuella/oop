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
	if (users.size() < getCount()) {
		users.push_back(user);
		return true;
	}
	return false;
}

bool Book::Return(User* user)
{
	vector<User*>::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		if (*it == user) {
			users.erase(it);
			return true;
		}
	}
	return false;
}