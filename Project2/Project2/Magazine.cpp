
#include "Magazine.h"

string Magazine::getHo() {
	return ho;
}
void Magazine::setHo(string newHo) {
	ho = newHo;
}

size_t Magazine::getCount() {
	return count;
}

void Magazine::setCount(size_t newCount) {
	count = newCount;
}

bool Magazine::Rent(User* user)
{
	if (users.size() < getCount()) {
		users.push_back(user);
		return true;
	}
	return false;
}

bool Magazine::Return(User* user)
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