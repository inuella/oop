#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// 유저 클래스.
class User
{
	friend class BookShop;
private:
	string name;      // 이름
	string birth;     // 생년월일
	string phone;     // 전화번호
	string address;   // 주소

public:
	User() { }
	// 유저 정보 출력.
	friend ostream& operator<<(ostream& o, User& user)
	{
		o << user.name << "\t" << user.birth << "\t";
		o << user.phone << "\t" << user.address << "\t";
		return o;
	}
};

// 도서 클래스.
class Book
{
	friend class BookShop;
private:
	string title;        // 도서 제목
	string publisher;    // 출판사
	size_t count;        // 전체 수량
	vector<User*> users; // 대여 유저 목록

public:
	Book() { count = 0; }
	// 도서 대여 처리.
	bool Rent(User* user)
	{
		if (users.size() < count) {
			users.push_back(user);
			return true;
		}
		return false;
	}
	// 도서 반납 처리.
	bool Return(User* user)
	{
		vector<User*>::iterator it;
		for (it = users.begin(); it != users.end(); it++) {
			if (*it == user) {
				users.erase(it);
				return true;
			}
		}
		return false;
	}
	// 도서 정보 출력.
	friend ostream& operator<<(ostream& o, Book& book)
	{
		o << book.title << "\t" << book.publisher << "\t";
		o << book.count - book.users.size() << "/" << book.count << "\t";
		return o;
	}
};

// 도서 대여점 클래스.
class BookShop
{
private:
	vector<Book> m_books;      // 도서 목록.
	vector<User> m_users;      // 유저 목록.

	// 유저 찾기 내부 함수.
	User* find_user(string name)
	{
		for (size_t i = 0; i < m_users.size(); i++)
		{
			if (m_users[i].name == name)
				return &m_users[i];
		}
		return NULL;
	}
	// 도서 찾기 내부 함수.
	Book* find_book(string title)
	{
		for (size_t i = 0; i < m_books.size(); i++)
		{
			if (m_books[i].title == title)
				return &m_books[i];
		}
		return NULL;
	}

public:
	// 생성자 - 파일 읽기.
	BookShop()
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
				userFile.getline(str, 100); user.name = str;
				userFile.getline(str, 100); user.birth = str;
				userFile.getline(str, 100); user.address = str;
				userFile.getline(str, 100); user.phone = str;
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
				bookFile.getline(str, 100); book.title = str;
				bookFile.getline(str, 100); book.publisher = str;
				bookFile.getline(str, 100); book.count = atoi(str);
				m_books.push_back(book);
			}
			bookFile.close();
		}
		// 대여 데이터 읽기.
		ifstream rentFile("rent.txt");
		if (!rentFile.fail())
		{
			char title[100], name[100];
			rentFile.getline(str, 100); count = atoi(str);
			for (int i = 0; i < count; i++)
			{
				rentFile.getline(title, 100);
				rentFile.getline(name, 100);
				User* user = find_user(name);
				Book* book = find_book(title);
				if (user && book) book->Rent(user);
			}
			rentFile.close();
		}
	}
	// 소멸자 - 파일 저장.
	~BookShop()
	{
		// 유저 데이터 저장.
		ofstream userFile("user.txt");
		if (!userFile.fail())
		{
			userFile << m_users.size() << endl;
			for (size_t i = 0; i < m_users.size(); i++)
			{
				userFile << m_users[i].name << endl;
				userFile << m_users[i].birth << endl;
				userFile << m_users[i].address << endl;
				userFile << m_users[i].phone << endl;
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
				bookFile << m_books[i].title << endl;
				bookFile << m_books[i].publisher << endl;
				bookFile << m_books[i].count << endl;
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
					rentFile << m_books[i].title << endl;
					rentFile << m_books[i].users[k]->name << endl;
				}
			}
			rentFile.close();
		}
	}
	// 유저 추가 함수.
	void AddUser()
	{
		char str[100];
		User user;
		cin.sync();
		cin.ignore();
		cout << "이름 : "; cin.getline(str, 100); user.name = str;
		cout << "생년월일 : "; cin.getline(str, 100); user.birth = str;
		cout << "전화번호 : "; cin.getline(str, 100); user.phone = str;
		cout << "주소 : "; cin.getline(str, 100); user.address = str;
		m_users.push_back(user);
		cout << "유저가 추가되었습니다." << endl;
		system("pause");
	}
	// 유저 삭제 함수
	void DeleteUser()
	{
		bool check = false;
		char str[100];
		User user;
		cin.sync();
		cin.ignore();
		cout << "이름 : "; cin.getline(str, 100);
		string name_ = str;
		cout << "생년월일 : "; cin.getline(str, 100);
		string birth_ = str;
		for (size_t i = 0; i < m_users.size(); i++) {
			if ((m_users[i].name == name_) && (m_users[i].birth == birth_)) {
				cout << "유저가 삭제 되었습니다." << endl;
				m_users.erase(m_users.begin() + i);
				check = true;
			}
		}
		if (check == false) {
			cout << "존재하지 않는 유저입니다." << endl;
		}
		system("pause");
	}
	// 도서 추가 함수.
	void AddBook()
	{
		char str[100];
		Book book;
		cin.sync();
		cin.ignore();
		cout << "제목 : "; cin.getline(str, 100); book.title = str;
		cout << "출판사 : "; cin.getline(str, 100); book.publisher = str;
		cout << "수량 : "; cin >> book.count;
		m_books.push_back(book);
		cout << "도서가 추가되었습니다." << endl;
		system("pause");
	}
	// 유저 검색 함수.
	void FindUser()
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
	void FindBook()
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
	// 도서 대여 함수.
	void RentBook()
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
				if (book->Rent(user)) cout << "도서 대여가 처리되었습니다." << endl;
				else cout << "입력하신 도서의 제고가 없습니다." << endl;
			}
			else cout << "입력하신 책이 존재하지 않습니다." << endl;
		}
		else cout << "입력하신 유저가 존재하지 않습니다." << endl;
		system("pause");
	}
	// 도서 반납 함수.
	void ReturnBook()
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
				else cout << "입력하신 도서의 제고가 없습니다." << endl;
			}
			else cout << "입력하신 책이 존재하지 않습니다." << endl;
		}
		else cout << "입력하신 유저가 존재하지 않습니다." << endl;
		system("pause");
	}
	// 도서 대여 목록 출력 함수.
	void RentList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "도서제목\t대여자\t전화번호" << endl;
		cout << "-------------------------------------------------------------" << endl;
		for (size_t i = 0; i < m_books.size(); i++) {
			for (size_t k = 0; k < m_books[i].users.size(); k++) {
				cout << m_books[i].title << "\t";
				cout << m_books[i].users[k]->name << "\t";
				cout << m_books[i].users[k]->phone << endl;
			}
		}
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}
	// 유저 목록 출력 함수.
	void UserList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "이름\t생년월일\t전화번호\t주소" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_users.size() == 0) cout << "등록된 유저가 업습니다." << endl;
		for (size_t i = 0; i < m_users.size(); i++) cout << m_users[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}
	// 도서 목록 출력 함수.
	void BookList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "제목\t출판사\t제고/전체수량" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_books.size() == 0) cout << "등록된 도서가 업습니다." << endl;
		for (size_t i = 0; i < m_books.size(); i++) cout << m_books[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}
};

// 메뉴 타이틀 및 카테고리 출력 함수.
void MenuTitle(char* s)
{
	system("cls");
	cout << "****************************************" << endl;
	cout << "****** 도 서 관 리 프 로 그 램 *********" << endl;
	cout << "****************************************" << endl;
	cout << s << endl;
}

// 메뉴 입력 함수.
int InputMenu(int max)
{
	int menu;
	while (true)
	{
		cin >> menu;
		if (menu >= 0 && menu <= max) break;
		cout << "잘못 입력하셨습니다. 다시 입력해 주세요 (0~" << max << ") : ";
	}
	return menu;
}

// 메인 함수.
int main()
{
	int menu;
	BookShop bookshop;

	while (1)
	{
		cout << "메뉴" << endl;
		cout << "1. 도서대여" << endl;
		cout << "2. 도서반납" << endl;
		cout << "3. 대여현황" << endl;
		cout << "4. 유저관리" << endl;
		cout << "5. 도서관리" << endl;
		cout << "0. 종료" << endl;
		cout << "> ";
		menu = InputMenu(5);

		switch (menu)
		{
		case 1:
			cout << "도서대여" << endl;
			bookshop.RentBook();
			break;
		case 2:
			cout << "도서반납" << endl;
			bookshop.ReturnBook();
			break;
		case 3:
			cout << "대여현황" << endl;
			bookshop.RentList();
			break;
		case 4:
			cout << "유저관리" << endl;
			cout << "1. 유저등록" << endl;
			cout << "2. 유저삭제" << endl;
			cout << "3. 유저검색" << endl;
			cout << "4. 유저목록" << endl;
			cout << "0. 돌아가기" << endl;
			cout << "> ";
			menu = InputMenu(4);
			switch (menu)
			{
			case 1:
				cout << "유저등록" << endl;
				bookshop.AddUser();
				break;
			case 2:
				cout << "유저삭제" << endl;
				bookshop.DeleteUser();
				break;
			case 3:
				cout << "유저검색" << endl;
				bookshop.FindUser();
				break;
			case 4:
				cout << "유저목록" << endl;
				bookshop.UserList();
				break;
			case 0: break;
			}
			break;
		case 5:
			cout << "도서관리" << endl;
			cout << "1. 도서등록" << endl;
			cout << "2. 도서검색" << endl;
			cout << "3. 도서목록" << endl;
			cout << "0. 돌아가기" << endl;
			cout << "> ";
			menu = InputMenu(3);
			switch (menu)
			{
			case 1:
				cout << "도서등록" << endl;
				bookshop.AddBook();
				break;
			case 2:
				cout << "도서검색" << endl;
				bookshop.FindBook();
				break;
			case 3:
				cout << "도서목록" << endl;
				bookshop.BookList();
				break;
			case 0: break;
			}
			break;	
		case 0:
			return 0;
		}
	}
	return 0;
}