

#include "UserData.h"


User* UserData::find_user(string name) {
	for (size_t i = 0; i < m_users.size(); i++)
	{
		if (m_users[i]->getName() == name)
			return m_users[i];
	}
	return NULL;
}

void UserData::getList() {
	for (int i = 0; i < getUsers().size(); i++) {
		cout << getUsers()[i]->getName() << "\t" << getUsers()[i]->getBirth() << "\t";
		cout << getUsers()[i]->getPhone() << "\t" << getUsers()[i]->getAddress() << "\t";
		cout << getUsers()[i]->getDueDate() << "\t" << getUsers()[i]->getAvailability();
	}
}

vector<User*>& UserData::getUsers() {
	return m_users;
}

void UserData::readUserData() {
	int count;
	char str[100];
	ifstream userFile("user.txt");
	if (!userFile.fail())
	{
		userFile.getline(str, 100); count = atoi(str);
		for (int i = 0; i < count; i++)
		{
			User* user = new User;
			userFile.getline(str, 100); user->setName(str);
			userFile.getline(str, 100); user->setBirth(str);
			userFile.getline(str, 100); user->setAddress(str);
			userFile.getline(str, 100); user->setPhone(str);
			userFile.getline(str, 100); user->setDueDate(str);
			userFile.getline(str, 100); user->setAvailability(str);
			getUsers().push_back(user);
		}
		userFile.close();
	}
}

void UserData::writeUserData() {
	ofstream userFile("user.txt");
	if (!userFile.fail())
	{
		userFile << getUsers().size() << endl;
		for (size_t i = 0; i < m_users.size(); i++)
		{
			userFile << getUsers()[i]->getName() << endl;
			userFile << getUsers()[i]->getBirth() << endl;
			userFile << getUsers()[i]->getAddress() << endl;
			userFile << getUsers()[i]->getPhone() << endl;
			userFile << getUsers()[i]->getDueDate() << endl;
			userFile << getUsers()[i]->getAvailability() << endl;
		}
		userFile.close();
	}
}

void UserData::FindUser()
{
	char name[100];
	cin.sync();
	cin.ignore();
	cout << "이름 : "; cin.getline(name, 100);
	User* user = find_user(name);
	if (user) cout << user->getName() << " 유저는 존재합니다." << endl;
	else cout << "검색하려는 유저가 존재하지 않습니다." << endl;
	system("pause");
}

void UserData::UserList() {

	cout << "-------------------------------------------------------------" << endl;
	cout << "이름\t생년월일\t전화번호\t주소\t대여날짜\t대여가능여부" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if (getUsers().size() == 0) cout << "등록된 유저가 없습니다." << endl;
	getList();
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;
	system("pause");

}

void UserData::AddUser()
{
	char str[100];
	User* user = new User;
	cin.sync();
	cin.ignore();
	cout << "이름 : "; cin.getline(str, 100);
	User* finduser = find_user(str);
	if (finduser != NULL && finduser->getName() == str) {
		cout << "이미 등록된 유저입니다." << endl;
		return;
	}
	user->setName(str);
	cout << "생년월일 : "; cin.getline(str, 100); user->setBirth(str);
	cout << "전화번호 : "; cin.getline(str, 100); user->setPhone(str);
	cout << "주소 : "; cin.getline(str, 100); user->setAddress(str);
	user->setDueDate("정보 없음");
	user->setAvailability("대여 가능");
	getUsers().push_back(user);
	cout << "유저가 추가되었습니다." << endl;
	system("pause");
}

void UserData::recoverAvailability() {

	cin.sync();
	cin.ignore();
	char str[100];
	cout << "이름 : "; cin.getline(str, 100);
	User* user = find_user(str);
	if (user != NULL) {
		if (user->getAvailability() == "대여 불가") {
			cout << "관리자 권한으로 대여 불가가 해제되었습니다." << endl;
			user->setAvailability("대여 가능");
		}
		else {
			cout << "해당 유저는 대여가 불가능한 상태가 아닙니다." << endl;
		}
	}
	else {
		cout << "해당 유저가 존재하지 않습니다." << endl;
	}
	system("pause");
}