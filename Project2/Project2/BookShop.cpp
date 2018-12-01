
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// ���� �뿩�� Ŭ����.
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


	// ������ - ���� �б�.
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
	// �Ҹ��� - ���� ����.
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
		// �뿩 ������ ����.
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
		cout << "���� : "; cin.getline(str, 100);
		Book* findbook = find_book(str);
		if (findbook != NULL && findbook->getName() == str) {
			cout << "�̹� ��ϵ� å�Դϴ�" << endl;
			return;
		}
		book.setName(str);
		cout << "���ǻ� : "; cin.getline(str, 100); book.setPublisher(str);
		cout << "���� : "; cin >> temp; book.setCount(temp);
		m_books.push_back(book);
		cout << "������ �߰��Ǿ����ϴ�." << endl;
		system("pause");
	}


	void BookShop::Find()
	{
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "å���� : "; cin.getline(title, 100);
		Book* book = find_book(title);
		if (book) cout << book->getName() << " å�� �����մϴ�." << endl;
		else cout << "�˻��Ϸ��� å�� �������� �ʽ��ϴ�." << endl;
		system("pause");
	}

	void BookShop::Rent()
	{
		char name[100];
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "�����̸� : "; cin.getline(name, 100);
		User* user = find_user(name);
		if (user)
		{
			cout << "�������� : "; cin.getline(title, 100);
			Book* book = find_book(title);
			if (book) {
				if (book->getUsers().size() < book->getCount()) {
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

	void BookShop::Return()
	{
		char name[100];
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "�����̸� : "; cin.getline(name, 100);
		User* user = find_user(name);
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
		cout << "��������\t�뿩��\t��ȭ��ȣ\t�뿩��¥\t[����]" << endl;
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

	// ���� ��� ��� �Լ�.
	void BookShop::List()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "����\t���ǻ�\t����/��ü����\t[����]" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_books.size() == 0) cout << "��ϵ� ������ �����ϴ�." << endl;
		for (size_t i = 0; i < m_books.size(); i++) cout << m_books[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
	}

