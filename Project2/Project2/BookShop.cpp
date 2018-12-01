
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// 도서 대여점 클래스.
#include "BookShop.h"
#include <time.h>



	Book* BookShop::find_book(string title)
	{
		for (size_t i = 0; i < m_books.size(); i++)
		{
			if (m_books[i].getName() == title)
				return &m_books[i];
		}
		return NULL;
	}

	User* BookShop::find_user(string name) {
		return userData.find_user(name);
	}


	// 생성자 - 파일 읽기.
	BookShop::BookShop()
	{
		int count;
		char str[100];

		ifstream bookFile("book.txt");
		if (!bookFile.fail())
		{
			bookFile.getline(str, 100); count = atoi(str);
			for (int i = 0; i < count; i++)
			{
				Book book;
				bookFile.getline(str, 100); book.setName(str);
				bookFile.getline(str, 100); book.setPublisher(str);
				bookFile.getline(str, 100); book.setCount(atoi(str));
				m_books.push_back(book);
			}
			bookFile.close();
		}
		// 대여 데이터 읽기.
		ifstream rentFile("rentbook.txt");
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
				Book* book = find_book(title);
				if (user && book) {
					user->setDueDate(dueDate);
					book->Rent(user);
				}
			}
			rentFile.close();
		}
	}
	// 소멸자 - 파일 저장.
	BookShop::~BookShop()
	{


		ofstream bookFile("book.txt");
		if (!bookFile.fail())
		{
			bookFile << m_books.size() << endl;
			for (size_t i = 0; i < m_books.size(); i++)
			{
				bookFile << m_books[i].getName() << endl;
				bookFile << m_books[i].getPublisher() << endl;
				bookFile << m_books[i].getCount() << endl;
			}
			bookFile.close();
		}
		// 대여 데이터 저장.
		ofstream rentFile("rentbook.txt");
		if (!rentFile.fail())
		{
			int count = 0;
			for (size_t i = 0; i < m_books.size(); i++) {
				count += m_books[i].getUsers().size();
			}
			rentFile << count << endl;
			for (size_t i = 0; i < m_books.size(); i++)
			{
				for (size_t k = 0; k < m_books[i].getUsers().size(); k++)
				{
					rentFile << m_books[i].getName() << endl;
					rentFile << m_books[i].getUsers()[k]->getName() << endl;
					rentFile << m_books[i].getUsers()[k]->getDueDate() << endl;
				}
			}
			rentFile.close();
		}
	}

	void BookShop::Add()
	{
		char str[100];
		size_t temp;
		Book book;
		cin.sync();
		cin.ignore();
		cout << "제목 : "; cin.getline(str, 100);
		Book* findbook = find_book(str);
		if (findbook != NULL && findbook->getName() == str) {
			cout << "이미 등록된 책입니다" << endl;
			return;
		}
		book.setName(str);
		cout << "출판사 : "; cin.getline(str, 100); book.setPublisher(str);
		cout << "수량 : "; cin >> temp; book.setCount(temp);
		m_books.push_back(book);
		cout << "도서가 추가되었습니다." << endl;
		system("pause");
	}


	void BookShop::Find()
	{
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "책제목 : "; cin.getline(title, 100);
		Book* book = find_book(title);
		if (book) cout << book->getName() << " 책은 존재합니다." << endl;
		else cout << "검색하려는 책이 존재하지 않습니다." << endl;
		system("pause");
	}

	void BookShop::Rent()
	{
		char name[100];
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "유저이름 : "; cin.getline(name, 100);
		User* user = find_user(name);
		if (user)
		{
			cout << "도서제목 : "; cin.getline(title, 100);
			Book* book = find_book(title);
			if (book) {
				if (book->getUsers().size() < book->getCount()) {
						if (user->getAvailability() == "대여 가능") {
						string time = timeCheck();
						cout << "도서 대여가 처리되었습니다." << endl;
						cout << "대여날짜: " << time << endl;
						user->setDueDate(time);
						book->Rent(user);
					}
					else cout << "이전의 도서연체로 인해 대여가 불가능한 상태입니다." << endl;

				}
				else cout << "입력하신 도서의 제고가 없습니다." << endl;
			}
			else cout << "입력하신 책이 존재하지 않습니다." << endl;
		}
		else cout << "입력하신 유저가 존재하지 않습니다." << endl;
		system("pause");
	}

	void BookShop::Return()
	{
		char name[100];
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "유저이름 : "; cin.getline(name, 100);
		User* user = find_user(name);
		if (user)
		{
			cout << "도서제목 : "; cin.getline(title, 100);
			Book* book = find_book(title);
			if (book) {
				if (book->Return(user)) {
						cout << "도서 반납이 처리되었습니다." << endl;
						if (compareTime(user) == false && user->getDueDate() != "정보 없음") {
							cout << "도서 연체입니다. 도서를 빌릴 수 없습니다." << endl;
							user->setAvailability("대여 불가");
						}
						user->setDueDate("정보 없음");

				}
				else cout << "입력하신 도서의 제고가 없습니다." << endl;
			}
			else cout << "입력하신 책이 존재하지 않습니다." << endl;
		}
		else cout << "입력하신 유저가 존재하지 않습니다." << endl;
		system("pause");
	}

	bool BookShop::compareTime(User* user) {
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
	// 도서 대여 목록 출력 함수.
	void BookShop::RentList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "도서제목\t대여자\t전화번호\t대여날짜\t[도서]" << endl;
		cout << "-------------------------------------------------------------" << endl;
		for (size_t i = 0; i < m_books.size(); i++) {
			for (size_t k = 0; k < m_books[i].getUsers().size(); k++) {
				if (m_books[i].getUsers()[k] != NULL) {
					cout << m_books[i].getName() << "\t";
					cout << m_books[i].getUsers()[k]->getName() << "\t";
					cout << m_books[i].getUsers()[k]->getPhone() << "\t";
					cout << m_books[i].getUsers()[k]->getDueDate() << endl;
				}
			}
		}
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}

	// 도서 목록 출력 함수.
	void BookShop::List()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "제목\t출판사\t제고/전체수량\t[도서]" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_books.size() == 0) cout << "등록된 도서가 없습니다." << endl;
		for (size_t i = 0; i < m_books.size(); i++) cout << m_books[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
	}

