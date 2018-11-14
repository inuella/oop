#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// ���� Ŭ����.
class User
{
	friend class BookShop;
private:
	string name;      // �̸�
	string birth;     // �������
	string phone;     // ��ȭ��ȣ
	string address;   // �ּ�

public:
	User() { }
	// ���� ���� ���.
	friend ostream& operator<<(ostream& o, User& user)
	{
		o << user.name << "\t" << user.birth << "\t";
		o << user.phone << "\t" << user.address << "\t";
		return o;
	}
};

// ���� Ŭ����.
class Book
{
	friend class BookShop;
private:
	string title;        // ���� ����
	string publisher;    // ���ǻ�
	size_t count;        // ��ü ����
	vector<User*> users; // �뿩 ���� ���

public:
	Book() { count = 0; }
	// ���� �뿩 ó��.
	bool Rent(User* user)
	{
		if (users.size() < count) {
			users.push_back(user);
			return true;
		}
		return false;
	}
	// ���� �ݳ� ó��.
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
	// ���� ���� ���.
	friend ostream& operator<<(ostream& o, Book& book)
	{
		o << book.title << "\t" << book.publisher << "\t";
		o << book.count - book.users.size() << "/" << book.count << "\t";
		return o;
	}
};

// ���� �뿩�� Ŭ����.
class BookShop
{
private:
	vector<Book> m_books;      // ���� ���.
	vector<User> m_users;      // ���� ���.

	// ���� ã�� ���� �Լ�.
	User* find_user(string name)
	{
		for (size_t i = 0; i < m_users.size(); i++)
		{
			if (m_users[i].name == name)
				return &m_users[i];
		}
		return NULL;
	}
	// ���� ã�� ���� �Լ�.
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
	// ������ - ���� �б�.
	BookShop()
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
	~BookShop()
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
	void AddUser()
	{
		char str[100];
		User user;
		cin.sync();
		cin.ignore();
		cout << "�̸� : "; cin.getline(str, 100); user.name = str;
		cout << "������� : "; cin.getline(str, 100); user.birth = str;
		cout << "��ȭ��ȣ : "; cin.getline(str, 100); user.phone = str;
		cout << "�ּ� : "; cin.getline(str, 100); user.address = str;
		m_users.push_back(user);
		cout << "������ �߰��Ǿ����ϴ�." << endl;
		system("pause");
	}
	// ���� ���� �Լ�
	void DeleteUser()
	{
		bool check = false;
		char str[100];
		User user;
		cin.sync();
		cin.ignore();
		cout << "�̸� : "; cin.getline(str, 100);
		string name_ = str;
		cout << "������� : "; cin.getline(str, 100);
		string birth_ = str;
		for (size_t i = 0; i < m_users.size(); i++) {
			if ((m_users[i].name == name_) && (m_users[i].birth == birth_)) {
				cout << "������ ���� �Ǿ����ϴ�." << endl;
				m_users.erase(m_users.begin() + i);
				check = true;
			}
		}
		if (check == false) {
			cout << "�������� �ʴ� �����Դϴ�." << endl;
		}
		system("pause");
	}
	// ���� �߰� �Լ�.
	void AddBook()
	{
		char str[100];
		Book book;
		cin.sync();
		cin.ignore();
		cout << "���� : "; cin.getline(str, 100); book.title = str;
		cout << "���ǻ� : "; cin.getline(str, 100); book.publisher = str;
		cout << "���� : "; cin >> book.count;
		m_books.push_back(book);
		cout << "������ �߰��Ǿ����ϴ�." << endl;
		system("pause");
	}
	// ���� �˻� �Լ�.
	void FindUser()
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
	void FindBook()
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
	void RentBook()
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
				else cout << "�Է��Ͻ� ������ ���� �����ϴ�." << endl;
			}
			else cout << "�Է��Ͻ� å�� �������� �ʽ��ϴ�." << endl;
		}
		else cout << "�Է��Ͻ� ������ �������� �ʽ��ϴ�." << endl;
		system("pause");
	}
	// ���� �ݳ� �Լ�.
	void ReturnBook()
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
	void RentList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "��������\t�뿩��\t��ȭ��ȣ" << endl;
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
	// ���� ��� ��� �Լ�.
	void UserList()
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
	void BookList()
	{
		cout << "-------------------------------------------------------------" << endl;
		cout << "����\t���ǻ�\t����/��ü����" << endl;
		cout << "-------------------------------------------------------------" << endl;
		if (m_books.size() == 0) cout << "��ϵ� ������ �����ϴ�." << endl;
		for (size_t i = 0; i < m_books.size(); i++) cout << m_books[i] << endl;
		cout << "-------------------------------------------------------------" << endl;
		system("pause");
	}
};

// �޴� Ÿ��Ʋ �� ī�װ� ��� �Լ�.
void MenuTitle(char* s)
{
	system("cls");
	cout << "****************************************" << endl;
	cout << "****** �� �� �� �� �� �� �� �� *********" << endl;
	cout << "****************************************" << endl;
	cout << s << endl;
}

// �޴� �Է� �Լ�.
int InputMenu(int max)
{
	int menu;
	while (true)
	{
		cin >> menu;
		if (menu >= 0 && menu <= max) break;
		cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ��� (0~" << max << ") : ";
	}
	return menu;
}

// ���� �Լ�.
int main()
{
	int menu;
	BookShop bookshop;

	while (1)
	{
		cout << "�޴�" << endl;
		cout << "1. �����뿩" << endl;
		cout << "2. �����ݳ�" << endl;
		cout << "3. �뿩��Ȳ" << endl;
		cout << "4. ��������" << endl;
		cout << "5. ��������" << endl;
		cout << "0. ����" << endl;
		cout << "> ";
		menu = InputMenu(5);

		switch (menu)
		{
		case 1:
			cout << "�����뿩" << endl;
			bookshop.RentBook();
			break;
		case 2:
			cout << "�����ݳ�" << endl;
			bookshop.ReturnBook();
			break;
		case 3:
			cout << "�뿩��Ȳ" << endl;
			bookshop.RentList();
			break;
		case 4:
			cout << "��������" << endl;
			cout << "1. �������" << endl;
			cout << "2. ��������" << endl;
			cout << "3. �����˻�" << endl;
			cout << "4. �������" << endl;
			cout << "0. ���ư���" << endl;
			cout << "> ";
			menu = InputMenu(4);
			switch (menu)
			{
			case 1:
				cout << "�������" << endl;
				bookshop.AddUser();
				break;
			case 2:
				cout << "��������" << endl;
				bookshop.DeleteUser();
				break;
			case 3:
				cout << "�����˻�" << endl;
				bookshop.FindUser();
				break;
			case 4:
				cout << "�������" << endl;
				bookshop.UserList();
				break;
			case 0: break;
			}
			break;
		case 5:
			cout << "��������" << endl;
			cout << "1. �������" << endl;
			cout << "2. �����˻�" << endl;
			cout << "3. �������" << endl;
			cout << "0. ���ư���" << endl;
			cout << "> ";
			menu = InputMenu(3);
			switch (menu)
			{
			case 1:
				cout << "�������" << endl;
				bookshop.AddBook();
				break;
			case 2:
				cout << "�����˻�" << endl;
				bookshop.FindBook();
				break;
			case 3:
				cout << "�������" << endl;
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