
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// ���� �뿩�� Ŭ����.
#include "DVDShop.h"

// ���� ã�� ���� �Լ�.
DVD* DVDShop::find_dvd(string title)
{
	for (size_t i = 0; i < m_dvds.size(); i++)
	{
		if (m_dvds[i].getName() == title)
			return &m_dvds[i];
	}
	return NULL;
}

User* DVDShop::find_user(string name) {
	return userData.find_user(name);
}


// ������ - ���� �б�.
DVDShop::DVDShop()
{
	int count;
	char str[100];
	ifstream bookFile("dvd.txt");
	if (!bookFile.fail())
	{
		bookFile.getline(str, 100); count = atoi(str);
		for (int i = 0; i < count; i++)
		{
			DVD dvd;
			bookFile.getline(str, 100); dvd.setName(str);
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
			User* user = find_user(name);
			DVD* dvd = find_dvd(title);
			if (user && dvd) {
				user->setDueDate(dueDate);
				dvd->Rent(user);
			}
		}
		rentFile.close();
	}
}

DVDShop::~DVDShop()
{

	ofstream bookFile("dvd.txt");
	if (!bookFile.fail())
	{
		bookFile << m_dvds.size() << endl;
		for (size_t i = 0; i < m_dvds.size(); i++)
		{
			bookFile << m_dvds[i].getName() << endl;
			bookFile << m_dvds[i].getMaker() << endl;
			bookFile << m_dvds[i].getCount() << endl;
		}
		bookFile.close();
	}

	ofstream rentFile("dvdrent.txt");
	if (!rentFile.fail())
	{
		int count = 0;
		for (size_t i = 0; i < m_dvds.size(); i++) {
			count += m_dvds[i].getUsers().size();
		}
		rentFile << count << endl;
		for (size_t i = 0; i < m_dvds.size(); i++)
		{
			for (size_t k = 0; k < m_dvds[i].getUsers().size(); k++)
			{
				rentFile << m_dvds[i].getName() << endl;
				rentFile << m_dvds[i].getUsers()[k]->getName() << endl;
				rentFile << m_dvds[i].getUsers()[k]->getDueDate() << endl;
			}
		}
		rentFile.close();
	}
}


void DVDShop::Add()
{
	char str[100];
	size_t temp;
	DVD dvd;
	cin.sync();
	cin.ignore();
	cout << "���� : "; cin.getline(str, 100); 
	DVD* finddvd = find_dvd(str);
	if (finddvd != NULL && finddvd->getName() == str) {
		cout << "�̹� ��ϵ� DVD�Դϴ�" << endl;
		return;
	}
	dvd.setName(str);
	cout << "���ۻ� : "; cin.getline(str, 100); dvd.setMaker(str);
	cout << "���� : "; cin >> temp; dvd.setCount(temp);
	m_dvds.push_back(dvd);
	cout << "DVD�� �߰��Ǿ����ϴ�." << endl;
	system("pause");
}

void DVDShop::Find()
{
	char title[100];
	cin.sync();
	cin.ignore();
	cout << "���� : "; cin.getline(title, 100);
	DVD* dvd = find_dvd(title);
	if (dvd) cout << dvd->getName() << " DVD�� �����մϴ�." << endl;
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
	User* user = find_user(name);
	if (user)
	{
		cout << "DVD���� : "; cin.getline(title, 100);
		DVD* dvd = find_dvd(title);
		if (dvd) {
			if (dvd->getUsers().size() < dvd->getCount()) {
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
	User* user = find_user(name);
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

bool DVDShop::compareTime(User* user) {
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
	cout << "DVD����\t�뿩��\t��ȭ��ȣ\t�뿩��¥\t[DVD]" << endl;
	cout << "-------------------------------------------------------------" << endl;
	for (size_t i = 0; i < m_dvds.size(); i++) {
		for (size_t k = 0; k < m_dvds[i].getUsers().size(); k++) {
			cout << m_dvds[i].getName() << "\t";
			cout << m_dvds[i].getUsers()[k]->getName() << "\t";
			cout << m_dvds[i].getUsers()[k]->getPhone() << "\t";
			cout << m_dvds[i].getUsers()[k]->getDueDate() << endl;
		}
	}
	cout << "-------------------------------------------------------------" << endl;
	system("pause");
}

void DVDShop::List()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "����\t���ۻ�\t����/��ü����\t[DVD]" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if (m_dvds.size() == 0) cout << "��ϵ� DVD�� �����ϴ�." << endl;
	for (size_t i = 0; i < m_dvds.size(); i++) cout << m_dvds[i] << endl;
	cout << "-------------------------------------------------------------" << endl;
	system("pause");
}
