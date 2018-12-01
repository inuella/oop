

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
	cout << "�̸� : "; cin.getline(name, 100);
	User* user = find_user(name);
	if (user) cout << user->getName() << " ������ �����մϴ�." << endl;
	else cout << "�˻��Ϸ��� ������ �������� �ʽ��ϴ�." << endl;
	system("pause");
}

void UserData::UserList() {

	cout << "-------------------------------------------------------------" << endl;
	cout << "�̸�\t�������\t��ȭ��ȣ\t�ּ�\t�뿩��¥\t�뿩���ɿ���" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if (getUsers().size() == 0) cout << "��ϵ� ������ �����ϴ�." << endl;
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
	cout << "�̸� : "; cin.getline(str, 100);
	User* finduser = find_user(str);
	if (finduser != NULL && finduser->getName() == str) {
		cout << "�̹� ��ϵ� �����Դϴ�." << endl;
		return;
	}
	user->setName(str);
	cout << "������� : "; cin.getline(str, 100); user->setBirth(str);
	cout << "��ȭ��ȣ : "; cin.getline(str, 100); user->setPhone(str);
	cout << "�ּ� : "; cin.getline(str, 100); user->setAddress(str);
	user->setDueDate("���� ����");
	user->setAvailability("�뿩 ����");
	getUsers().push_back(user);
	cout << "������ �߰��Ǿ����ϴ�." << endl;
	system("pause");
}

void UserData::recoverAvailability() {

	cin.sync();
	cin.ignore();
	char str[100];
	cout << "�̸� : "; cin.getline(str, 100);
	User* user = find_user(str);
	if (user != NULL) {
		if (user->getAvailability() == "�뿩 �Ұ�") {
			cout << "������ �������� �뿩 �Ұ��� �����Ǿ����ϴ�." << endl;
			user->setAvailability("�뿩 ����");
		}
		else {
			cout << "�ش� ������ �뿩�� �Ұ����� ���°� �ƴմϴ�." << endl;
		}
	}
	else {
		cout << "�ش� ������ �������� �ʽ��ϴ�." << endl;
	}
	system("pause");
}