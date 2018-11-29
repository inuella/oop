
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// ���� �뿩�� Ŭ����.
#include "DVDShop.h"


vector<DVD> m_dvds;      // ���� ���.
vector<DVDUser> m_users;      // ���� ���.

// ���� ã�� ���� �Լ�.
DVDUser* DVDShop::find_user(string name)
{
	for (size_t i = 0; i < m_users.size(); i++)
	{
		if (m_users[i].getName() == name)
			return &m_users[i];
	}
	return NULL;
}
// ���� ã�� ���� �Լ�.
DVD* DVDShop::find_dvd(string title)
{
	for (size_t i = 0; i < m_dvds.size(); i++)
	{
		if (m_dvds[i].getTitle() == title)
			return &m_dvds[i];
	}
	return NULL;
}




// ������ - ���� �б�.
DVDShop::DVDShop()
{
	int count;
	char str[100];
	// ���� ������ �б�
	ifstream userFile("dvduser.txt");
	if (!userFile.fail())
	{
		userFile.getline(str, 100); count = atoi(str);
		for (int i = 0; i < count; i++)
		{
			DVDUser user;
			userFile.getline(str, 100); user.setName(str);
			userFile.getline(str, 100); user.setBirth(str);
			userFile.getline(str, 100); user.setAddress(str);
			userFile.getline(str, 100); user.setPhone(str);
			userFile.getline(str, 100); user.setDueDate(str);
			userFile.getline(str, 100); user.setAvailability(str);
			// ���� ������ �б�.
			m_users.push_back(user);
		}
		userFile.close();
	}
	ifstream bookFile("dvd.txt");
	if (!bookFile.fail())
	{
		bookFile.getline(str, 100); count = atoi(str);
		for (int i = 0; i < count; i++)
		{
			DVD dvd;
			bookFile.getline(str, 100); dvd.setTitle(str);
			bookFile.getline(str, 100); dvd.setMaker(str);
			bookFile.getline(str, 100); dvd.setCount(atoi(str));
			m_dvds.push_back(dvd);
		}
		bookFile.close();
	}
	// �뿩 ������ �б�.
	ifstream rentFile("dvdrent.txt");
	if (!rentFile.fail())
	{
		char title[100], name[100], dueDate[100];
		rentFile.getline(str, 100); count = atoi(str);
		for (int i = 0; i < count; i++)
		{
			rentFile.getline(title, 100);
			rentFile.getline(name, 100);
			rentFile.getline(dueDate, 100);
			DVDUser* user = find_user(name);
			DVD* dvd = find_dvd(title);
			if (user && dvd) {
				user->setDueDate(dueDate);
				dvd->Rent(user);
			}
		}
		rentFile.close();
	}
}
// �Ҹ��� - ���� ����.
DVDShop::~DVDShop()
{
	// ���� ������ ����.
	ofstream userFile("dvduser.txt");
	if (!userFile.fail())
	{
		userFile << m_users.size() << endl;
		for (size_t i = 0; i < m_users.size(); i++)
		{
			userFile << m_users[i].getName() << endl;
			userFile << m_users[i].getBirth() << endl;
			userFile << m_users[i].getAddress() << endl;
			userFile << m_users[i].getPhone() << endl;
			userFile << m_users[i].getDueDate() << endl;
			userFile << m_users[i].getAvailability() << endl;
		}
		userFile.close();
	}
	// ���� ������ ����.
	ofstream bookFile("dvd.txt");
	if (!bookFile.fail())
	{
		bookFile << m_dvds.size() << endl;
		for (size_t i = 0; i < m_dvds.size(); i++)
		{
			bookFile << m_dvds[i].getTitle() << endl;
			bookFile << m_dvds[i].getMaker() << endl;
			bookFile << m_dvds[i].getCount() << endl;
		}
		bookFile.close();
	}
	// �뿩 ������ ����.
	ofstream rentFile("dvdrent.txt");
	if (!rentFile.fail())
	{
		int count = 0;
		for (size_t i = 0; i < m_dvds.size(); i++) {
			count += m_dvds[i].users.size();
		}
		rentFile << count << endl;
		for (size_t i = 0; i < m_dvds.size(); i++)
		{
			for (size_t k = 0; k < m_dvds[i].users.size(); k++)
			{
				rentFile << m_dvds[i].getTitle() << endl;
				rentFile << m_dvds[i].users[k]->getName() << endl;
				rentFile << m_dvds[i].users[k]->getDueDate() << endl;
			}
		}
		rentFile.close();
	}
}
// ���� �߰� �Լ�.
void DVDShop::AddUser()
{
	char str[100];
	DVDUser user;
	cin.sync();
	cin.ignore();
	cout << "�̸� : "; cin.getline(str, 100);		
	DVDUser* finduser = find_user(str);
	if (finduser != NULL && finduser->getName() == str) {
		cout << "�̹� ��ϵ� �����Դϴ�." << endl;
		return;
	}
	user.setName(str);

	cout << "������� : "; cin.getline(str, 100); user.setBirth(str);
	cout << "��ȭ��ȣ : "; cin.getline(str, 100); user.setPhone(str);
	cout << "�ּ� : "; cin.getline(str, 100); user.setAddress(str);
	user.setDueDate("���� ����");
	user.setAvailability("�뿩 ����");
	m_users.push_back(user);
	cout << "������ �߰��Ǿ����ϴ�." << endl;
	system("pause");
}
// ���� �߰� �Լ�.
void DVDShop::Add()
{
	char str[100];
	size_t temp;
	DVD dvd;
	cin.sync();
	cin.ignore();
	cout << "���� : "; cin.getline(str, 100); 
	DVD* finddvd = find_dvd(str);
	if (finddvd != NULL && finddvd->getTitle() == str) {
		cout << "�̹� ��ϵ� DVD�Դϴ�" << endl;
		return;
	}
	dvd.setTitle(str);
	cout << "���ۻ� : "; cin.getline(str, 100); dvd.setMaker(str);
	cout << "���� : "; cin >> temp; dvd.setCount(temp);
	m_dvds.push_back(dvd);
	cout << "DVD�� �߰��Ǿ����ϴ�." << endl;
	system("pause");
}
// ���� �˻� �Լ�.
void DVDShop::FindUser()
{
	char name[100];
	cin.sync();
	cin.ignore();
	cout << "�̸� : "; cin.getline(name, 100);
	DVDUser* user = find_user(name);
	if (user) cout << user->getName() << " ������ �����մϴ�."  << endl;
	else cout << "�˻��Ϸ��� ������ �������� �ʽ��ϴ�." << endl;
	system("pause");
}
// ���� �˻� �Լ�.
void DVDShop::Find()
{
	char title[100];
	cin.sync();
	cin.ignore();
	cout << "���� : "; cin.getline(title, 100);
	DVD* dvd = find_dvd(title);
	if (dvd) cout << dvd->getTitle() << " DVD�� �����մϴ�." << endl;
	else cout << "�˻��Ϸ��� DVD�� �������� �ʽ��ϴ�." << endl;
	system("pause");
}
// ���� �뿩 �Լ�.
void DVDShop::Rent()
{
	char name[100];
	char title[100];
	cin.sync();
	cin.ignore();
	cout << "�����̸� : "; cin.getline(name, 100);
	DVDUser* user = find_user(name);
	if (user)
	{
		cout << "DVD���� : "; cin.getline(title, 100);
		DVD* dvd = find_dvd(title);
		if (dvd) {
			if (dvd->users.size() < dvd->getCount()) {
				if (user->getAvailability() == "�뿩 ����") {
					string time = timeCheck();
					cout << "DVD �뿩�� ó���Ǿ����ϴ�." << endl;
					cout << "�뿩��¥: " << time << endl;
					user->setDueDate(time);
					dvd->Rent(user);
				}
				else cout << "������ DVD��ü�� ���� �뿩�� �Ұ����� �����Դϴ�." << endl;

			}
			else cout << "�Է��Ͻ� DVD�� ���� �����ϴ�." << endl;
		}
		else cout << "�Է��Ͻ� DVD�� �������� �ʽ��ϴ�." << endl;
	}
	else cout << "�Է��Ͻ� ������ �������� �ʽ��ϴ�." << endl;
	system("pause");
}
// ���� �ݳ� �Լ�.
void DVDShop::Return()
{
	char name[100];
	char title[100];
	cin.sync();
	cin.ignore();
	cout << "�����̸� : "; cin.getline(name, 100);
	DVDUser* user = find_user(name);
	if (user)
	{
		cout << "DVD���� : "; cin.getline(title, 100);
		DVD* dvd = find_dvd(title);
		if (dvd) {
			if (dvd->Return(user)) {
				cout << "DVD �ݳ��� ó���Ǿ����ϴ�." << endl;
				if (compareTime(user) == false && user->getDueDate() != "���� ����") {
					cout << "DVD ��ü�Դϴ�. DVD�� ���� �� �����ϴ�." << endl;
					user->setAvailability("�뿩 �Ұ�");
				}
				user->setDueDate("���� ����");

			}
			else cout << "�Է��Ͻ� DVD�� ���� �����ϴ�." << endl;
		}
		else cout << "�Է��Ͻ� å�� �������� �ʽ��ϴ�." << endl;
	}
	else cout << "�Է��Ͻ� ������ �������� �ʽ��ϴ�." << endl;
	system("pause");
}

bool DVDShop::compareTime(DVDUser* user) {
	string time = timeCheck();
	const char* str1; const char* str2;	const char* str3; const char* str4; const char* str5; const char* str6;


	string currentYear = time.substr(0, 4);
	str1 = currentYear.c_str();
	int cY = atoi(str1);
	string currentMonth = time.substr(7, 2);
	str2 = currentMonth.c_str();
	int cM = atoi(str2);
	string currentDay = time.substr(11, 2);
	str3 = currentDay.c_str();
	int cD = atoi(str3);




	string userTime = user->getDueDate();

	if (userTime != "���� ����") {
		string userYear = userTime.substr(0, 4);
		str4 = userYear.c_str();
		int uY = atoi(str4);
		string userMonth = userTime.substr(7, 2);
		str5 = userYear.c_str();
		int uM = atoi(str5);
		string userDay = userTime.substr(11, 2);
		str6 = userDay.c_str();
		int uD = atoi(str6);

		if (cY == uY) {
			if (cM == uM) {
				if (cD <= uD + 10)
					return true;
				else
					return false;
			}
			else if (cM == uM + 1) {
				if (cD + 30 <= uD + 10)
					return true;
			}
			else
				return false;
		}

		else if (cY == uY + 1) {
			if (cM == 1 && uM == 12) {
				if (cD + 31 <= uD + 10) {
					return true;
				}
			}
		}

		else
			return false;
	}

	return false;


}
// ���� �뿩 ��� ��� �Լ�.
void DVDShop::RentList()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "DVD����\t�뿩��\t��ȭ��ȣ\t�뿩��¥" << endl;
	cout << "-------------------------------------------------------------" << endl;
	for (size_t i = 0; i < m_dvds.size(); i++) {
		for (size_t k = 0; k < m_dvds[i].users.size(); k++) {
			cout << m_dvds[i].getTitle() << "\t";
			cout << m_dvds[i].users[k]->getName() << "\t";
			cout << m_dvds[i].users[k]->getPhone() << "\t";
			cout << m_dvds[i].users[k]->getDueDate() << endl;
		}
	}
	cout << "-------------------------------------------------------------" << endl;
	system("pause");
}
// ���� ��� ��� �Լ�.
void DVDShop::UserList()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "�̸�\t�������\t��ȭ��ȣ\t�ּ�\t�뿩��¥\t�뿩���ɿ���" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if (m_users.size() == 0) cout << "��ϵ� ������ �����ϴ�." << endl;
	for (size_t i = 0; i < m_users.size(); i++) cout << m_users[i] << endl;
	cout << "-------------------------------------------------------------" << endl;
	system("pause");
}
// ���� ��� ��� �Լ�.
void DVDShop::List()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "����\t���ۻ�\t����/��ü����" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if (m_dvds.size() == 0) cout << "��ϵ� DVD�� �����ϴ�." << endl;
	for (size_t i = 0; i < m_dvds.size(); i++) cout << m_dvds[i] << endl;
	cout << "-------------------------------------------------------------" << endl;
	system("pause");
}

void DVDShop::recoverAvailability() {
	char str[100];
	cin.sync();
	cin.ignore();
	cout << "�̸� : "; cin.getline(str, 100);
	DVDUser* user = find_user(str);
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