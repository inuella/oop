#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
#include "Book.h"
#include "BookShop.h"

using namespace std;




// �޴� Ÿ��Ʋ �� ī�װ� ��� �Լ�.
void MenuTitle(const char* s)
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

	MenuTitle("");


	while (1)
	{
		cout << "�޴�" << endl;
		cout << "1. �����뿩" << endl;
		cout << "2. �����ݳ�" << endl;
		cout << "3. �뿩��Ȳ" << endl;
		cout << "4. ��������" << endl;
		cout << "5. ��������" << endl;
		cout << "6. ��õ����" << endl;
		cout << "0. ����" << endl;
		cout << "> ";
		menu = InputMenu(6);

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
			cout << "2. �����˻�" << endl;
			cout << "3. �������" << endl;
			cout << "0. ���ư���" << endl;
			cout << "> ";
			menu = InputMenu(3);
			switch (menu)
			{
			case 1:
				cout << "�������" << endl;
				bookshop.AddUser();
				break;
			case 2:
				cout << "�����˻�" << endl;
				bookshop.FindUser();
				break;
			case 3:
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
		case 6:
			cout << "  ��õ �����Դϴ�." << endl;
			bookshop.RandomBook();
			break;
		case 0:
			return 0;
		}
	}
	return 0;
}