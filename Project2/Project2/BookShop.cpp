
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// ���� �뿩�� Ŭ����.
#include "BookShop.h"
#include <time.h>


	vector<Book> m_books;      // ���� ���.
	vector<User> m_users;      // ���� ���.

	// ���� ã�� ���� �Լ�.
	BookUser* BookShop::find_user(string name)
	{
		for (size_t i = 0; i < m_users.size(); i++)
		{
			if (m_users[i].getName() == name)
				return &m_users[i];
		}
		return NULL;
	}
	// ���� ã�� ���� �Լ�.
	Book* BookShop::find_book(string title)
	{
		for (size_t i = 0; i < m_books.size(); i++)
		{
			if (m_books[i].getTitle() == title)
				return &m_books[i];
		}
		return NULL;
	}


	// ������ - ���� �б�.
	BookShop::BookShop()
	{
		int count;
		int count2;
		char str[100];
		// ���� ������ �б�
		ifstream userFile("bookuser.txt");
		if (!userFile.fail())
		{
			userFile.getline(str, 100); count = atoi(str);
			for (int i = 0; i < count; i++)
			{
				BookUser user;
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
		// �뿩 ������ �б�.
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
				BookUser* user = find_user(name);
				Book* book = find_book(title);
				if (user && book) {
					user->setDueDate(dueDate);
					book->Rent(user);
				}
			}
			rentFile.close();
		}
	}
	// �Ҹ��� - ���� ����.
	BookShop::~BookShop()
	{
		// ���� ������ ����.
		ofstream userFile("bookuser.txt");
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
		// �뿩 ������ ����.
		ofstream rentFile("rentbook.txt");
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
	// ���� �߰� �Լ�.
	void BookShop::AddUser()
	{
		char str[100];
		BookUser user;
		cin.sync();
		cin.ignore();
		cout << "�̸� : "; cin.getline(str, 100); 
		BookUser* finduser = find_user(str);
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
	void BookShop::Add()
	{
		char str[100];
		size_t temp;
		Book book;
		cin.sync();
		cin.ignore();
		cout << "���� : "; cin.getline(str, 100);
		Book* findbook = find_book(str);
		if (findbook != NULL && findbook->getTitle() == str) {
			cout << "�̹� ��ϵ� å�Դϴ�" << endl;
			return;
		}
		book.setTitle(str);
		cout << "���ǻ� : "; cin.getline(str, 100); book.setPublisher(str);
		cout << "���� : "; cin >> temp; book.setCount(temp);
		m_books.push_back(book);
		cout << "������ �߰��Ǿ����ϴ�." << endl;
		system("pause");
	}
	// ���� �˻� �Լ�.
	void BookShop::FindUser()
	{
		char name[100];
		cin.sync();
		cin.ignore();
		cout << "�̸� : "; cin.getline(name, 100);
		BookUser* user = find_user(name);
		if (user) cout << user->getName() << " ������ �����մϴ�." << endl;
		else cout << "�˻��Ϸ��� ������ �������� �ʽ��ϴ�." << endl;
		system("pause");
	}
	// ���� �˻� �Լ�.
	void BookShop::Find()
	{
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "å���� : "; cin.getline(title, 100);
		Book* book = find_book(title);
		if (book) cout << book->getTitle() << " å�� �����մϴ�." << endl;
		else cout << "�˻��Ϸ��� å�� �������� �ʽ��ϴ�." << endl;
		system("pause");
	}
	// ���� �뿩 �Լ�.
	void BookShop::Rent()
	{
		char name[100];
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "�����̸� : "; cin.getline(name, 100);
		BookUser* user = find_user(name);
		if (user)
		{
			cout << "�������� : "; cin.getline(title, 100);
			Book* book = find_book(title);
			if (book) {
				if (book->users.size() < book->getCount()) {
						if (user->getAvailability() == "�뿩 ����") {
						string time = timeCheck();
						cout << "���� �뿩�� ó���Ǿ����ϴ�." << endl;
						cout << "�뿩��¥: " << time << endl;
						user->setDueDate(time);
						book->Rent(user);
					}
					else cout << "������ ������ü�� ���� �뿩�� �Ұ����� �����Դϴ�." << endl;

				}
				else cout << "�Է��Ͻ� ������ ���� �����ϴ�." << endl;
			}
			else cout << "�Է��Ͻ� å�� �������� �ʽ��ϴ�." << endl;
		}
		else cout << "�Է��Ͻ� ������ �������� �ʽ��ϴ�." << endl;
		system("pause");
	}
	// ���� �ݳ� �Լ�.
	void BookShop::Return()
	{
		char name[100];
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "�����̸� : "; cin.getline(name, 100);
		BookUser* user = find_user(name);
		if (user)
		{
			cout << "�������� : "; cin.getline(title, 100);
			Book* book = find_book(title);
			if (book) {
				if (book->Return(user)) {
						cout << "���� �ݳ��� ó���Ǿ����ϴ�." << endl;
						if (compareTime(user) == false && user->getDueDate() != "���� ����") {
							cout << "���� ��ü�Դϴ�. ������ ���� �� �����ϴ�." << endl;
							user->setAvailability("�뿩 �Ұ�");
						}
						user->setDueDate("���� ����");

				}
				else cout << "�Է��Ͻ� ������ ���� �����ϴ�." << endl;
			}
			else cout << "�Է��Ͻ� å�� �������� �ʽ��ϴ�." << endl;
		}
		else cout << "�Է��Ͻ� ������ �������� �ʽ��ϴ�." << endl;
		system("pause");
	}

	bool BookShop::compareTime(BookUser* user) {
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
	// ���� �뿩 ��� ��� �Լ�.
	void BookShop::RentList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "��������\t�뿩��\t��ȭ��ȣ\t�뿩��¥" << endl;
		cout << "-------------------------------------------------------------" << endl;
		for (size_t i = 0; i < m_books.size(); i++) {
			for (size_t k = 0; k < m_books[i].users.size(); k++) {
				if (m_books[i].users[k] != NULL) {
					cout << m_books[i].getTitle() << "\t";
					cout << m_books[i].users[k]->getName() << "\t";
					cout << m_books[i].users[k]->getPhone() << "\t";
					cout << m_books[i].users[k]->getDueDate() << endl;
				}
			}
		}
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}
	// ���� ��� ��� �Լ�.
	void BookShop::UserList()
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
	void BookShop::List()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "����\t���ǻ�\t����/��ü����" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_books.size() == 0) cout << "��ϵ� ������ �����ϴ�." << endl;
		for (size_t i = 0; i < m_books.size(); i++) cout << m_books[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}

	void BookShop::recoverAvailability() {
		
		cin.sync();
		cin.ignore();
		char str[100];
		cout << "�̸� : "; cin.getline(str, 100);
		BookUser* user = find_user(str);
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