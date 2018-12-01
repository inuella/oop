#pragma once
#include <vector>
#include "User.h"


class UserData {

private:
	vector<User*> m_users;

	void getList();

public:
	vector<User*>& getUsers();
	
	User* find_user(string name);

	void readUserData();

	void writeUserData();

	void recoverAvailability();

	void FindUser();

	void UserList();

	void AddUser();
};