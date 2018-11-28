// ���� �뿩�� Ŭ����.
#include "BookShop.h"
#include <algorithm> //std::random_shuffle
#include <time.h>


	vector<Book> m_books;      // ���� ���.
	vector<User> m_users;      // ���� ���.
	vector<Book>::iterator iter;

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
	// ���� ��õ ���� �Լ�.
	Book* BookShop::random_book()
	{
		int i = 0;
		for (i = 0; i < m_books.size(); i++) m_books[i];
		srand(time(NULL));
		random_shuffle(m_books.begin(), m_books.end());

		for (iter = m_books.begin(); iter != m_books.end(); iter++)
		{
		cout << *iter << endl;
		}
		cout << endl;
		return NULL;
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
				userFile.getline(str, 100); user.name = str;
				userFile.getline(str, 100); user.birth = str;
				userFile.getline(str, 100); user.address = str;
				userFile.getline(str, 100); user.phone = str;
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
				bookFile.getline(str, 100); book.title = str;
				bookFile.getline(str, 100); book.publisher = str;
				bookFile.getline(str, 100); book.count = atoi(str);
				m_books.push_back(book);
			}
			bookFile.close();
		}
		// �뿩 ������ �б�.
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
				userFile << m_users[i].name << endl;
				userFile << m_users[i].birth << endl;
				userFile << m_users[i].address << endl;
				userFile << m_users[i].phone << endl;
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
				bookFile << m_books[i].title << endl;
				bookFile << m_books[i].publisher << endl;
				bookFile << m_books[i].count << endl;
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
					rentFile << m_books[i].title << endl;
					rentFile << m_books[i].users[k]->name << endl;
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
		m_users.push_back(user);
		cout << "������ �߰��Ǿ����ϴ�." << endl;
		system("pause");
	}
	// ���� ���� �Լ�.
	void BookShop::DeleteUser() {
		char str[100];
		User user;
		bool check = false;
		cin.sync();
		cin.ignore();
		cout << "�̸� : "; cin.getline(str, 100);
		string name_ = str;
		cout << "������� : "; cin.getline(str, 100);
		string birth_ = str;
		for (size_t i = 0; i < m_users.size(); i++) {
			if ((m_users[i].getName() == name_)&&(m_users[i].getBirth() == birth_)) {
				cout << "������ �����Ǿ����ϴ�." << endl;
				m_users.erase(m_users.begin() + i);
				check = true;
			}
		}
		if (check == false) {
			cout << "�������� �ʴ� �����Դϴ�.";
		}
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
	// ���� ���� �Լ�.
	void BookShop::DeleteBook() {
		char str[100];
		Book book;
		bool check = false;
		size_t i;
		cin.sync();
		cin.ignore();
		cout << "���� : "; cin.getline(str, 100);
		string title_ = str;
		for (i = 0; i < m_books.size(); i++) {
			if (m_books[i].getTitle() == title_) {
				cout << "������ �����Ǿ����ϴ�." << endl;
				m_books.erase(m_books.begin() + i);
				check = true;
			}
		}
		if (check == false) {
			cout << "�������� �ʴ� �����Դϴ�.";
		}
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
	// ���� ��õ �Լ�.
	void BookShop::RandomBook()
	{
		cout << random_book() << endl;
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
				if (book->Rent(user)) cout << "���� �뿩�� ó���Ǿ����ϴ�." << endl;
				else cout << "�Է��Ͻ� ������ ��� �����ϴ�." << endl;
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
				else cout << "�Է��Ͻ� ������ ��� �����ϴ�." << endl;
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
		cout << "��������\t�뿩��\t��ȭ��ȣ" << endl;
		cout << "-------------------------------------------------------------" << endl;
		for (size_t i = 0; i < m_books.size(); i++) {
			for (size_t k = 0; k < m_books[i].users.size(); k++) {
				cout << m_books[i].getTitle() << "\t";
				cout << m_books[i].users[k]->getName() << "\t";
				cout << m_books[i].users[k]->getPhone() << endl;
			}
		}
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}
	// ���� ��� ��� �Լ�.
	void BookShop::UserList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "�̸�\t�������\t��ȭ��ȣ\t�ּ�" << endl;
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
		cout << "����\t���ǻ�\t���/��ü����" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_books.size() == 0) cout << "��ϵ� ������ �����ϴ�." << endl;
		for (size_t i = 0; i < m_books.size(); i++) cout << m_books[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}
