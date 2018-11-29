#pragma once
#include "Book.h"

Book::Book() {
	setCount(0);
}
string Book::getTitle() {
	return title;
}
string Book::getPublisher() {
	return publisher;
}
size_t Book::getCount() {
	return count;
}


void Book::setTitle(string newTitle) {
	title = newTitle;
}
void Book::setPublisher(string newPublisher) {
	publisher = newPublisher;
}
void Book::setCount(size_t newCount) {
	count = newCount;
}


bool Book::Rent(BookUser* user)
{
	if (users.size() < getCount()) {
		users.push_back(user);
		return true;
	}
	return false;
}
// 도서 반납 처리.
bool Book::Return(BookUser* user)
{
	vector<BookUser*>::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		if (*it == user) {
			users.erase(it);
			return true;
		}
	}
	return false;
}