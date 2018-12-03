#include "User.h"

string User::getName() {
	return name;
}
string User::getBirth() {
	return birth;
}
string User::getPhone() {
	return phone;
}
string User::getAddress() {
	return address;
}
string User::getDueDate() {
	return dueDate;
}
string User::getAvailability() {
	return availability;
}



void User::setName(string newName) {
	name = newName;
}
void User::setBirth(string newBirth) {
	birth = newBirth;
}
void User::setPhone(string newPhone) {
	phone = newPhone;
}
void User::setAddress(string newAddress) {
	address = newAddress;
}
void User::setDueDate(string newDueDate) {
	dueDate = newDueDate;
}
void User::setAvailability(string newAvailability) {
	availability = newAvailability;
}
