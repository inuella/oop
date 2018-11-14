
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// ���� �뿩�� Ŭ����.
#include "BookShop.h"
#include <time.h>
#include "Book.h"
#include "User.h"


	vector<Book> m_books;      // ���� ���.
	vector<User> m_users;      // ���� ���.

	// ���� ã�� ���� �Լ�.
	User* BookShop::find_user(string name)
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

	string BookShop::timeCheck() {
		time_t now;
		time(&now);
		string s; // ���� �� �� ����ð� ����
		s = asctime(localtime(&now));
		string str1 = s.substr(4, 3); // ��
		string str2 = s.substr(8, 2); // ��
		string str3 = s.substr(11, 2); // ��
		string str4 = s.substr(20, 4); // ����
		return str4 + "�� " + str1 + "�� " + str2 + "�� " + str3 + "�� ";
	}


	// ������ - ���� �б�.
	BookShop::BookShop()
	{
		int count;
		char str[100];
		// ���� ������ �б�
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
		// ���� ������ �б�.
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
	// �Ҹ��� - ���� ����.
	BookShop::~BookShop()
	{
		// ���� ������ ����.
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
	// ���� �߰� �Լ�.
	void BookShop::AddUser()
	{
		char str[100];
		User user;
		cin.sync();
		cin.ignore();
		cout << "�̸� : "; cin.getline(str, 100); user.setName(str);
		cout << "������� : "; cin.getline(str, 100); user.setBirth(str);
		cout << "��ȭ��ȣ : "; cin.getline(str, 100); user.setPhone(str);
		cout << "�ּ� : "; cin.getline(str, 100); user.setAddress(str);
		user.setDueDate("���� ����");
		m_users.push_back(user);
		cout << "������ �߰��Ǿ����ϴ�." << endl;
		system("pause");
	}
	// ���� �߰� �Լ�.
	void BookShop::AddBook()
	{
		char str[100];
		size_t temp;
		Book book;
		cin.sync();
		cin.ignore();
		cout << "���� : "; cin.getline(str, 100); book.setTitle(str);
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
		User* user = find_user(name);
		if (user) cout << user << endl;
		else cout << "�˻��Ϸ��� ������ �������� �ʽ��ϴ�." << endl;
		system("pause");
	}
	// ���� �˻� �Լ�.
	void BookShop::FindBook()
	{
		char title[100];
		cin.sync();
		cin.ignore();
		cout << "å���� : "; cin.getline(title, 100);
		Book* book = find_book(title);
		if (book) cout << book << endl;
		else cout << "�˻��Ϸ��� å�� �������� �ʽ��ϴ�." << endl;
		system("pause");
	}
	// ���� �뿩 �Լ�.
	void BookShop::RentBook()
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
					
					string time = timeCheck();
					cout << "���� �뿩�� ó���Ǿ����ϴ�." << endl;
					cout << "�뿩��¥: " << time << endl;
					user->setDueDate(time);
					book->Rent(user);

				}
				else cout << "�Է��Ͻ� ������ ���� �����ϴ�." << endl;
			}
			else cout << "�Է��Ͻ� å�� �������� �ʽ��ϴ�." << endl;
		}
		else cout << "�Է��Ͻ� ������ �������� �ʽ��ϴ�." << endl;
		system("pause");
	}
	// ���� �ݳ� �Լ�.
	void BookShop::ReturnBook()
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
				if (book->Return(user)) cout << "���� �ݳ��� ó���Ǿ����ϴ�." << endl;
				else cout << "�Է��Ͻ� ������ ���� �����ϴ�." << endl;
			}
			else cout << "�Է��Ͻ� å�� �������� �ʽ��ϴ�." << endl;
		}
		else cout << "�Է��Ͻ� ������ �������� �ʽ��ϴ�." << endl;
		system("pause");
	}
	// ���� �뿩 ��� ��� �Լ�.
	void BookShop::RentList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "��������\t�뿩��\t��ȭ��ȣ\t�뿩��¥" << endl;
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
	// ���� ��� ��� �Լ�.
	void BookShop::UserList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "�̸�\t�������\t��ȭ��ȣ\t�ּ�\t�뿩��¥" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_users.size() == 0) cout << "��ϵ� ������ �����ϴ�." << endl;
		for (size_t i = 0; i < m_users.size(); i++) cout << m_users[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}
	// ���� ��� ��� �Լ�.
	void BookShop::BookList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "����\t���ǻ�\t����/��ü����" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_books.size() == 0) cout << "��ϵ� ������ �����ϴ�." << endl;
		for (size_t i = 0; i < m_books.size(); i++) cout << m_books[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}

