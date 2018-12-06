
#include "MagazineShop.h"

Magazine* MagazineShop::find_magazine(string title)
{
	for (size_t i = 0; i < m_magazines.size(); i++)
	{
		if (m_magazines[i].getName() == title)
			return &m_magazines[i];
	}
	return NULL;
}


// 생성자 - 파일 읽기.
MagazineShop::MagazineShop()
{
	int count;
	char str[100];
	readUserData();

	ifstream magazineFile("magazine.txt");
	if (!magazineFile.fail())
	{
		magazineFile.getline(str, 100); count = atoi(str);
		for (int i = 0; i < count; i++)
		{
			Magazine magazine;
			magazineFile.getline(str, 100); magazine.setName(str);
			magazineFile.getline(str, 100); magazine.setHo(str);
			magazineFile.getline(str, 100); magazine.setCount(atoi(str));
			m_magazines.push_back(magazine);
		}
		magazineFile.close();
	}
	// 대여 데이터 읽기.
	ifstream rentFile("rentmagazine.txt");
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
			Magazine* magazine = find_magazine(title);
			if (user && magazine) {
				user->setDueDate(dueDate);
				magazine->Rent(user);
			}
		}
		rentFile.close();
	}
}
// 소멸자 - 파일 저장.
MagazineShop::~MagazineShop()
{
	writeUserData();

	ofstream magazineFile("magazine.txt");
	if (!magazineFile.fail())
	{
		magazineFile << m_magazines.size() << endl;
		for (size_t i = 0; i < m_magazines.size(); i++)
		{
			magazineFile << m_magazines[i].getName() << endl;
			magazineFile << m_magazines[i].getHo() << endl;
			magazineFile << m_magazines[i].getCount() << endl;
		}
		magazineFile.close();
	}
	// 대여 데이터 저장.
	ofstream rentFile("rentmagazine.txt");
	if (!rentFile.fail())
	{
		int count = 0;
		for (size_t i = 0; i < m_magazines.size(); i++) {
			count += m_magazines[i].users.size();
		}
		rentFile << count << endl;
		for (size_t i = 0; i < m_magazines.size(); i++)
		{
			for (size_t k = 0; k < m_magazines[i].users.size(); k++)
			{
				rentFile << m_magazines[i].getName() << endl;
				rentFile << m_magazines[i].users[k]->getName() << endl;
				rentFile << m_magazines[i].users[k]->getDueDate() << endl;
			}
		}
		rentFile.close();
	}

}

void MagazineShop::Add()
{
	char str[100];
	char str2[100];
	size_t temp;
	Magazine magazine;
	cin.sync();
	cin.ignore();
	cout << "제목 : "; cin.getline(str, 100);
	cout << "호수 : "; cin.getline(str2, 100);
	Magazine* findmagazine = find_magazine(str);
	if (findmagazine != NULL && findmagazine->getName() == str && findmagazine->getHo() == str2) {
		cout << "이미 등록된 잡지입니다." << endl;
		return;
	}
	magazine.setName(str);
	magazine.setHo(str2);
	cout << "수량 : "; cin >> temp; magazine.setCount(temp);
	m_magazines.push_back(magazine);
	cout << "잡지가 추가되었습니다." << endl;
	system("pause");
}


void MagazineShop::Find()
{
	char title[100];
	cin.sync();
	cin.ignore();
	cout << "책제목 : "; cin.getline(title, 100);
	Magazine* magazine = find_magazine(title);
	if (magazine) cout << magazine->getName() << " 잡지는 존재합니다." << endl;
	else cout << "검색하려는 잡지가 존재하지 않습니다." << endl;
	system("pause");
}

void MagazineShop::Rent()
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
		cout << "잡지제목 : "; cin.getline(title, 100);
		Magazine* magazine = find_magazine(title);
		if (magazine) {
			if (magazine->users.size() < magazine->getCount()) {
				if (user->getAvailability() == "대여 가능") {
					string time = timeCheck();
					cout << "잡지 대여가 처리되었습니다." << endl;
					cout << "대여날짜: " << time << endl;
					user->setDueDate(time);
					magazine->Rent(user);
				}
				else cout << "이전의 연체로 인해 대여가 불가능한 상태입니다." << endl;

			}
			else cout << "입력하신 잡지의 재고가 없습니다." << endl;
		}
		else cout << "입력하신 잡지가 존재하지 않습니다." << endl;
	}
	else cout << "입력하신 유저가 존재하지 않습니다." << endl;
	system("pause");
}

void MagazineShop::Return()
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
		cout << "잡지제목 : "; cin.getline(title, 100);
		Magazine* magazine = find_magazine(title);
		if (magazine) {
			if (magazine->Return(user)) {
				cout << "잡지 반납이 처리되었습니다." << endl;
				if (compareTime(user) == false && user->getDueDate() != "정보 없음") {
					cout << "연체입니다. 잡지를 빌릴 수 없습니다." << endl;
					user->setAvailability("대여 불가");
				}
				user->setDueDate("정보 없음");

			}
			else cout << "입력하신 잡지의 재고가 없습니다." << endl;
		}
		else cout << "입력하신 잡지가 존재하지 않습니다." << endl;
	}
	else cout << "입력하신 유저가 존재하지 않습니다." << endl;
	system("pause");
}

bool MagazineShop::compareTime(User* user) {
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
		str5 = userMonth.c_str();
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

void MagazineShop::RentList()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "잡지제목\t대여자\t전화번호\t대여날짜\t[잡지]" << endl;
	cout << "-------------------------------------------------------------" << endl;
	for (size_t i = 0; i < m_magazines.size(); i++) {
		for (size_t k = 0; k < m_magazines[i].users.size(); k++) {
			if (m_magazines[i].users[k] != NULL) {
				cout << m_magazines[i].getName() << "\t";
				cout << m_magazines[i].users[k]->getName() << "\t";
				cout << m_magazines[i].users[k]->getPhone() << "\t";
				cout << m_magazines[i].users[k]->getDueDate() << endl;
			}
		}
	}
	cout << "-------------------------------------------------------------" << endl;
	system("pause");
}

// 도서 목록 출력 함수.
void MagazineShop::List()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "제목\t호수\t재고/전체수량\t[잡지]" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if (m_magazines.size() == 0) cout << "등록된 잡지가 없습니다." << endl;
	for (size_t i = 0; i < m_magazines.size(); i++) cout << m_magazines[i] << endl;
	cout << "-------------------------------------------------------------" << endl;
}

void MagazineShop::readUserData() {
	int count;
	char str[100];
	ifstream userFile("magazineuser.txt");
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

void MagazineShop::writeUserData() {
	ofstream userFile("magazineuser.txt");
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


void MagazineShop::getList() {
	for (size_t i = 0; i < m_users.size(); i++) {
		cout << m_users[i].getName() << "\t" << m_users[i].getBirth() << "\t";
		cout << m_users[i].getPhone() << "\t" << m_users[i].getAddress() << "\t";
		cout << m_users[i].getDueDate() << "\t" << m_users[i].getAvailability();
		if (i < m_users.size() - 1) {
			cout << endl;
		}
	}
}

User* MagazineShop::find_user(string name, string birth, string number) {
	for (size_t i = 0; i < m_users.size(); i++)
	{
		if (m_users[i].getName() == name && m_users[i].getBirth() == birth && m_users[i].getPhone() == number)
			return &m_users[i];
	}
	return NULL;
}

User* MagazineShop::find_user(string name) {
	for (size_t i = 0; i < m_users.size(); i++)
	{
		if (m_users[i].getName() == name)
			return &m_users[i];
	}
	return NULL;
}

void MagazineShop::FindUser()
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

void MagazineShop::UserList() {

	cout << "-------------------------------------------------------------" << endl;
	cout << "이름\t생년월일\t전화번호\t주소\t대여날짜\t대여가능여부" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if (m_users.size() == 0) cout << "등록된 유저가 없습니다." << endl;
	getList();
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;
	system("pause");

}

void MagazineShop::AddUser()
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

void MagazineShop::recoverAvailability() {

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