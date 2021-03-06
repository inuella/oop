
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// 도서 대여점 클래스.
#include "BookShop.h"
#include <time.h>
#include <algorithm>
#include "Book.h"
#include "User.h"


	vector<Book> m_books;      // 도서 목록.
	vector<User> m_users;      // 유저 목록.
	vector<Book>::iterator iter;

	// 유저 찾기 내부 함수.
	User* BookShop::find_user(string name)
	{
		for (size_t i = 0; i < m_users.size(); i++)
		{
			if (m_users[i].getName() == name)
				return &m_users[i];
		}
		return NULL;
	}
	// 도서 찾기 내부 함수.
	Book* BookShop::find_book(string title)
	{
		for (size_t i = 0; i < m_books.size(); i++)
		{
			if (m_books[i].getTitle() == title)
				return &m_books[i];
		}
		return NULL;
	}
	//도서 추천 내부 함수.
	Book* BookShop::random_book()
	{
		for (int i = 0; i < m_books.size(); i++) m_books[i];
		srand(time(NULL));
		random_shuffle(m_books.begin(), m_books.end()); //도서목록을 랜덤하게 섞어줌.

		cout << m_books.front() << endl << endl; //랜덤하게 배열한 것 중 택 1
		return NULL;
	}

	string BookShop::timeCheck() {
		time_t now;
		time(&now);
		string s; // 요일 월 일 현재시간 연도
		s = asctime(localtime(&now));
		string str1 = s.substr(4, 3); // 월
		string str2 = s.substr(8, 2); // 일
		string str3 = s.substr(11, 2); // 시
		string str4 = s.substr(20, 4); // 연도
		return str4 + "년 " + str1 + "월 " + str2 + "일 " + str3 + "시 ";
	}


	// 생성자 - 파일 읽기.
	BookShop::BookShop()
	{
		int count;
		char str[100];
		// 유저 데이터 읽기
		ifstream userFile("user.txt");
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
				m_users.push_back(user);
			}
			userFile.close();
		}
		// 도서 데이터 읽기.
		ifstream bookFile("book.txt");
		if (!bookFile.fail())
		{
			bookFile.getline(str, 100); count = atoi(str);
			for (int i = 0; i < count; i++)
			{
				Book book;
				bookFile.getline(str, 100); book.setTitle(str);
				bookFile.getline(str, 100); book.setPublisher(str);
				bookFile.getline(str, 100); book.setCount(atoi(str));
				m_books.push_back(book);
			}
			bookFile.close();
		}
		// 대여 데이터 읽기.
		ifstream rentFile("rent.txt");
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
		// 유저 데이터 저장.
		ofstream userFile("user.txt");
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
			}
			userFile.close();
		}
		// 도서 데이터 저장.
		ofstream bookFile("book.txt");
		if (!bookFile.fail())
		{
			bookFile << m_books.size() << endl;
			for (size_t i = 0; i < m_books.size(); i++)
			{
				bookFile << m_books[i].getTitle() << endl;
				bookFile << m_books[i].getPublisher() << endl;
				bookFile << m_books[i].getCount() << endl;
			}
			bookFile.close();
		}
		// 대여 데이터 저장.
		ofstream rentFile("rent.txt");
		if (!rentFile.fail())
		{
			int count = 0;
			for (size_t i = 0; i < m_books.size(); i++) {
				count += m_books[i].users.size();
			}
			rentFile << count << endl;
			for (size_t i = 0; i < m_books.size(); i++)
			{
				for (size_t k = 0; k < m_books[i].users.size(); k++)
				{
					rentFile << m_books[i].getTitle() << endl;
					rentFile << m_books[i].users[k]->getName() << endl;
					rentFile << m_books[i].users[k]->getDueDate() << endl;
				}
			}
			rentFile.close();
		}
	}
	// 유저 추가 함수.
	void BookShop::AddUser()
	{
		char str[100];
		User user;
		cin.sync();
		cin.ignore();
		cout << "이름 : "; cin.getline(str, 100); user.setName(str);
		cout << "생년월일 : "; cin.getline(str, 100); user.setBirth(str);
		cout << "전화번호 : "; cin.getline(str, 100); user.setPhone(str);
		cout << "주소 : "; cin.getline(str, 100); user.setAddress(str);
		user.setDueDate("정보 없음");
		m_users.push_back(user);
		cout << "유저가 추가되었습니다." << endl;
		system("pause");
	}
	// 유저 삭제 함수.
	void BookShop::DeleteUser() {
		char str[100];
		User user;
		bool check = false;
		cin.sync();
		cin.ignore();
		cout << "이름 : "; cin.getline(str, 100);
		string name_ = str;
		cout << "생년월일 : "; cin.getline(str, 100);
		string birth_ = str;
		for (size_t i = 0; i < m_users.size(); i++) {
			if ((m_users[i].getName() == name_) && (m_users[i].getBirth() == birth_)) {
				cout << "유저가 삭제되었습니다." << endl;
				m_users.erase(m_users.begin() + i);
				check = true;
			}
		}
		if (check == false) {
			cout << "존재하지 않는 유저입니다.";
		}
		system("pause");
	}
	// 도서 추가 함수.
	void BookShop::AddBook()
	{
		char str[100];
		size_t temp;
		Book book;
		cin.sync();
		cin.ignore();
		cout << "제목 : "; cin.getline(str, 100); book.setTitle(str);
		cout << "출판사 : "; cin.getline(str, 100); book.setPublisher(str);
		cout << "수량 : "; cin >> temp; book.setCount(temp);
		m_books.push_back(book);
		cout << "도서가 추가되었습니다." << endl;
		system("pause");
	}
	// 도서 삭제 함수.
	void BookShop::DeleteBook() {
		char str[100];
		Book book;
		bool check = false;
		size_t i;
		cin.sync();
		cin.ignore();
		cout << "제목 : "; cin.getline(str, 100);
		string title_ = str;
		for (i = 0; i < m_books.size(); i++) {
			if (m_books[i].getTitle() == title_) {
				cout << "도서가 삭제되었습니다." << endl;
				m_books.erase(m_books.begin() + i);
				check = true;
			}
		}
		if (check == false) {
			cout << "존재하지 않는 도서입니다.";
		}
		system("pause");
	}
	// 유저 검색 함수.
	void BookShop::FindUser()
	{
		char name[100];
		cin.sync();
		cin.ignore();
		cout << "이름 : "; cin.getline(name, 100);
		User* user = find_user(name);
		if (user) cout << user << endl;
		else cout << "검색하려는 유저가 존재하지 않습니다." << endl;
		system("pause");
	}
	// 도서 검색 함수.
	void BookShop::FindBook()
	{
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "책제목 : "; cin.getline(title, 100);
		Book* book = find_book(title);
		if (book) cout << book << endl;
		else cout << "검색하려는 책이 존재하지 않습니다." << endl;
		system("pause");
	}
	// 도서 추천 함수.
	void BookShop::RandomBook()
	{
		cout << random_book() << endl;
		system("pause");
	}
	// 도서 대여 함수.
	void BookShop::RentBook()
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
					
					string time = timeCheck();
					cout << "도서 대여가 처리되었습니다." << endl;
					cout << "대여날짜: " << time << endl;
					user->setDueDate(time);
					book->Rent(user);

				}
				else cout << "입력하신 도서의 재고가 없습니다." << endl;
			}
			else cout << "입력하신 책이 존재하지 않습니다." << endl;
		}
		else cout << "입력하신 유저가 존재하지 않습니다." << endl;
		system("pause");
	}
	// 도서 반납 함수.
	void BookShop::ReturnBook()
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
				if (book->Return(user)) cout << "도서 반납이 처리되었습니다." << endl;
				else cout << "입력하신 도서의 재고가 없습니다." << endl;
			}
			else cout << "입력하신 책이 존재하지 않습니다." << endl;
		}
		else cout << "입력하신 유저가 존재하지 않습니다." << endl;
		system("pause");
	}
	// 도서 대여 목록 출력 함수.
	void BookShop::RentList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "도서제목\t대여자\t전화번호\t대여날짜" << endl;
		cout << "-------------------------------------------------------------" << endl;
		for (size_t i = 0; i < m_books.size(); i++) {
			for (size_t k = 0; k < m_books[i].getUsers().size(); k++) {
				cout << m_books[i].getTitle() << "\t";
				cout << m_books[i].users[k]->getName() << "\t";
				cout << m_books[i].users[k]->getPhone() << "\t";
				cout << m_books[i].users[k]->getDueDate() << endl;
			}
		}
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}
	// 유저 목록 출력 함수.
	void BookShop::UserList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "이름\t생년월일\t전화번호\t주소\t대여날짜" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_users.size() == 0) cout << "등록된 유저가 없습니다." << endl;
		for (size_t i = 0; i < m_users.size(); i++) cout << m_users[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}
	// 도서 목록 출력 함수.
	void BookShop::BookList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "제목\t출판사\t재고/전체수량" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_books.size() == 0) cout << "등록된 도서가 없습니다." << endl;
		for (size_t i = 0; i < m_books.size(); i++) cout << m_books[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}

