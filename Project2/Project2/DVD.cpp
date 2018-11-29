#pragma once
#include "DVD.h"

DVD::DVD() {
	setCount(0);
}
string DVD::getTitle() {
	return title;
}
string DVD::getMaker() {
	return maker;
}
size_t DVD::getCount() {
	return count;
}


void DVD::setTitle(string newTitle) {
	title = newTitle;
}
void DVD::setMaker(string newMaker) {
	maker = newMaker;
}
void DVD::setCount(size_t newCount) {
	count = newCount;
}


bool DVD::Rent(DVDUser* user)
{
	if (users.size() < getCount()) {
		users.push_back(user);
		return true;
	}
	return false;
}
// 도서 반납 처리.
bool DVD::Return(DVDUser* user)
{
	vector<DVDUser*>::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		if (*it == user) {
			users.erase(it);
			return true;
		}
	}
	return false;
}