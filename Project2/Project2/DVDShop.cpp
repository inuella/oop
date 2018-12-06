
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include "DVDShop.h"


DVD* DVDShop::find_dvd(string title)
{
	for (size_t i = 0; i < m_dvds.size(); i++)
	{
		if (m_dvds[i].getName() == title)
			return &m_dvds[i];
	}
	return NULL;
}


DVDShop::DVDShop()
{
	int count;
	char str[100];
	readUserData();
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

	writeUserData();

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
			count += m_dvds[i].users.size();
		}
		rentFile << count << endl;
		for (size_t i = 0; i < m_dvds.size(); i++)
		{
			for (size_t k = 0; k < m_dvds[i].users.size(); k++)
			{
				rentFile << m_dvds[i].getName() << endl;
				rentFile << m_dvds[i].users[k]->getName() << endl;
				rentFile << m_dvds[i].users[k]->getDueDate() << endl;
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
	cout << "제목 : "; cin.getline(str, 100);
	DVD* finddvd = find_dvd(str);
	if (finddvd != NULL && finddvd->getName() == str) {
		cout << "이미 등록된 DVD입니다" << endl;
		return;
	}
	dvd.setName(str);
	cout << "제작사 : "; cin.getline(str, 100); dvd.setMaker(str);
	cout << "수량 : "; cin >> temp; dvd.setCount(temp);
	m_dvds.push_back(dvd);
	cout << "DVD가 추가되었습니다." << endl;
	system("pause");
}

void DVDShop::Find()
{
	char title[100];
	cin.sync();
	cin.ignore();
	cout << "제목 : "; cin.getline(title, 100);
	DVD* dvd = find_dvd(title);
	if (dvd) cout << dvd->getName() << " DVD는 존재합니다." << endl;
	else cout << "검색하려는 DVD가 존재하지 않습니다." << endl;
	system("pause");
}

void DVDShop::Rent()
{
	char name[100];
	char birth[100];
	char number[100];
	char title[100];
	cin.sync();
	cin.ignore();
	cout << "유저이름 : "; cin.getline(name, 100);
	cout << "생일 : "; cin.getline(birth, 100);
	cout << "전화번호 : "; cin.getline(number, 100);
	User* user = find_user(name, birth, number);
	if (user)
	{
		cout << "DVD제목 : "; cin.getline(title, 100);
		DVD* dvd = find_dvd(title);
		if (dvd) {
			if (dvd->users.size() < dvd->getCount()) {
				if (user->getAvailability() == "대여 가능") {
					string time = timeCheck();
					cout << "DVD 대여가 처리되었습니다." << endl;
					cout << "대여날짜: " << time << endl;
					user->setDueDate(time);
					dvd->Rent(user);
				}
				else cout << "이전의 DVD연체로 인해 대여가 불가능한 상태입니다." << endl;

			}
			else cout << "입력하신 DVD의 제고가 없습니다." << endl;
		}
		else cout << "입력하신 DVD가 존재하지 않습니다." << endl;
	}
	else cout << "입력하신 유저가 존재하지 않습니다." << endl;
	system("pause");
}

void DVDShop::Return()
{
	char name[100];
	char birth[100];
	char number[100];
	char title[100];
	cin.sync();
	cin.ignore();
	cout << "유저이름 : "; cin.getline(name, 100);
	cout << "생일 : "; cin.getline(birth, 100);
	cout << "전화번호 : "; cin.getline(number, 100);
	User* user = find_user(name, birth, number);
	if (user)
	{
		cout << "DVD제목 : "; cin.getline(title, 100);
		DVD* dvd = find_dvd(title);
		if (dvd) {
			if (dvd->Return(user)) {
				cout << "DVD 반납이 처리되었습니다." << endl;
				if (compareTime(user) == false && user->getDueDate() != "정보 없음") {
					cout << "DVD 연체입니다. DVD를 빌릴 수 없습니다." << endl;
					user->setAvailability("대여 불가");
				}
				user->setDueDate("정보 없음");

			}
			else cout << "입력하신 DVD의 제고가 없습니다." << endl;
		}
		else cout << "입력하신 책이 존재하지 않습니다." << endl;
	}
	else cout << "입력하신 유저가 존재하지 않습니다." << endl;
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

	if (userTime != "정보 없음") {
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

void DVDShop::RentList()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "DVD제목\t대여자\t전화번호\t대여날짜\t[DVD]" << endl;
	cout << "-------------------------------------------------------------" << endl;
	for (size_t i = 0; i < m_dvds.size(); i++) {
		for (size_t k = 0; k < m_dvds[i].users.size(); k++) {
			cout << m_dvds[i].getName() << "\t";
			cout << m_dvds[i].users[k]->getName() << "\t";
			cout << m_dvds[i].users[k]->getPhone() << "\t";
			cout << m_dvds[i].users[k]->getDueDate() << endl;
		}
	}
	cout << "-------------------------------------------------------------" << endl;
}

void DVDShop::List()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "제목\t제작사\t제고/전체수량\t[DVD]" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if (m_dvds.size() == 0) cout << "등록된 DVD가 없습니다." << endl;
	for (size_t i = 0; i < m_dvds.size(); i++) cout << m_dvds[i] << endl;
	cout << "-------------------------------------------------------------" << endl;
}

void DVDShop::readUserData() {
	int count;
	char str[100];
	ifstream userFile("dvduser.txt");
	if (!userFile.fail())
	{
		userFile.getline(str, 100); count = atoi(str);
		for (int i = 0; i < count; i++)
		{
			User user;
			userFile.getline(str, 100); user.setName(str);
			userFile.getline(str, 100); user.setBirth(str);
			userFile.getline(str, 100); user.setAddress(str);
			userFile.getline(str, 100); user.setPhone(str);
			userFile.getline(str, 100); user.setDueDate(str);
			userFile.getline(str, 100); user.setAvailability(str);
			m_users.push_back(user);
		}
		userFile.close();
	}
}

void DVDShop::writeUserData() {
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
}

void DVDShop::getList() {
	for (size_t i = 0; i < m_users.size(); i++) {
		cout << m_users[i].getName() << "\t" << m_users[i].getBirth() << "\t";
		cout << m_users[i].getPhone() << "\t" << m_users[i].getAddress() << "\t";
		cout << m_users[i].getDueDate() << "\t" << m_users[i].getAvailability();
		if (i < m_users.size() - 1) {
			cout << endl;
		}
	}
}

User* DVDShop::find_user(string name, string birth, string number) {
	for (size_t i = 0; i < m_users.size(); i++)
	{
		if (m_users[i].getName() == name && m_users[i].getBirth() == birth && m_users[i].getPhone() == number)
			return &m_users[i];
	}
	return NULL;
}

User* DVDShop::find_user(string name) {
	for (size_t i = 0; i < m_users.size(); i++)
	{
		if (m_users[i].getName() == name)
			return &m_users[i];
	}
	return NULL;
}

void DVDShop::FindUser()
{
	char name[100];
	char birth[100];
	char number[100];
	char title[100];
	cin.sync();
	cin.ignore();
	cout << "유저이름 : "; cin.getline(name, 100);
	cout << "생일 : "; cin.getline(birth, 100);
	cout << "전화번호 : "; cin.getline(number, 100);
	User* user = find_user(name, birth, number);
	if (user) cout << user->getName() << " 유저는 존재합니다." << endl;
	else cout << "검색하려는 유저가 존재하지 않습니다." << endl;
	system("pause");
}

void DVDShop::UserList() {

	cout << "-------------------------------------------------------------" << endl;
	cout << "이름\t생년월일\t전화번호\t주소\t대여날짜\t대여가능여부" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if (m_users.size() == 0) cout << "등록된 유저가 없습니다." << endl;
	getList();
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;
	system("pause");

}

void DVDShop::AddUser()
{
	char str[100];
	char str2[100];
	char str3[100];
	cin.sync();
	cin.ignore();
	User user;
	cout << "이름 : "; cin.getline(str, 100);
	cout << "생년월일 : "; cin.getline(str2, 100);
	cout << "전화번호 : "; cin.getline(str3, 100);
	User* finduser = find_user(str, str2, str3);
	if (finduser != NULL && finduser->getName() == str && finduser->getBirth() == str2 && finduser->getPhone() == str3) {
		cout << "동일한 정보를 가진 유저가 이미 존재합니다." << endl;
		return;
	}
	user.setName(str);
	user.setBirth(str2);
	user.setPhone(str3);
	cout << "주소 : "; cin.getline(str, 100); user.setAddress(str);
	user.setDueDate("정보 없음");
	user.setAvailability("대여 가능");
	m_users.push_back(user);
	cout << "유저가 추가되었습니다." << endl;
	system("pause");
}

void DVDShop::recoverAvailability() {

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