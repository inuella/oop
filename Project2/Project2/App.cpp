

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
#include "Book.h"
#include "BookShop.h"
#include "Shop.h"
#include "DVD.h"
#include "DVDShop.h"



using namespace std;


// �޴� Ÿ��Ʋ �� ī�װ� ��� �Լ�.
void MenuTitle(const char* s)
{
	system("cls");
	cout << "*************************************************" << endl;
	cout << "****** �� �� �� D V D �� �� �� �� �� �� *********" << endl;
	cout << "*************************************************" << endl;
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

int BookMenu() {
	int menu;
	BookShop bookshop;

	while (1) {
		cout << "�����뿩" << endl;
		cout << "1. �����뿩" << endl;
		cout << "2. �����ݳ�" << endl;
		cout << "3. �뿩��Ȳ" << endl;
		cout << "4. ��������" << endl;
		cout << "5. ��������" << endl;
		cout << "6. (����������) �뿩�Ұ� ����" << endl;
		cout << "0. ���ư���" << endl;
		cout << "> ";
		menu = InputMenu(6);

		switch (menu)
		{
		case 1:
			cout << "�����뿩" << endl;
			bookshop.Rent();
			break;
		case 2:
			cout << "�����ݳ�" << endl;
			bookshop.Return();
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
			case 0: 
				break;
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
				bookshop.Add();
				break;
			case 2:
				cout << "�����˻�" << endl;
				bookshop.Find();
				break;
			case 3:
				cout << "�������" << endl;
				bookshop.List();
				break;
			case 0: 
				break;
			}
			break;

		case 6:
			bookshop.recoverAvailability();
			break;

		case 0:
			return 0;
		}

	}
	return 0;
}

int DVDMenu() {

	int menu;
	DVDShop dvdshop;


	while (1) {
		cout << "DVD�뿩" << endl;
		cout << "1. DVD�뿩" << endl;
		cout << "2. DVD�ݳ�" << endl;
		cout << "3. �뿩��Ȳ" << endl;
		cout << "4. ��������" << endl;
		cout << "5. DVD����" << endl;
		cout << "6. (����������) �뿩�Ұ� ����" << endl;
		cout << "0. ���ư���" << endl;
		cout << "> ";
		menu = InputMenu(5);

		switch (menu)
		{
		case 1:
			cout << "DVD�뿩" << endl;
			dvdshop.Rent();
			break;
		case 2:
			cout << "DVD�ݳ�" << endl;
			dvdshop.Return();
			break;
		case 3:
			cout << "�뿩��Ȳ" << endl;
			dvdshop.RentList();
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
				dvdshop.AddUser();
				break;
			case 2:
				cout << "�����˻�" << endl;
				dvdshop.FindUser();
				break;
			case 3:
				cout << "�������" << endl;
				dvdshop.UserList();
				break;
			case 0: 
				break;
			}
			break;

		case 5:
			cout << "DVD����" << endl;
			cout << "1. DVD���" << endl;
			cout << "2. DVD�˻�" << endl;
			cout << "3. DVD���" << endl;
			cout << "0. ���ư���" << endl;
			cout << "> ";
			menu = InputMenu(3);
			switch (menu)
			{
			case 1:
				cout << "DVD���" << endl;
				dvdshop.Add();
				break;
			case 2:
				cout << "DVD�˻�" << endl;
				dvdshop.Find();
				break;
			case 3:
				cout << "DVD���" << endl;
				dvdshop.List();
				break;
			case 0:
				break;
			}
			break;

		case 6:
			dvdshop.recoverAvailability();
			break;
			
		case 0:
			return 0;
		}
	}
	return 0;
}


// ���� �Լ�.
int main()
{
	int menu;
	DVDShop dvdshop;

	MenuTitle("");

	while (1) {
		cout << "�޴�" << endl;
		cout << "1. �����޴�" << endl;
		cout << "2. DVD�޴�" << endl;
		cout << "0. ����" << endl;
		cout << "> ";
		menu = InputMenu(2);
		switch (menu)
		{
		case 1:
			BookMenu();
			break;

		case 2:
			DVDMenu();
			break;

		case 0:
			return 0;
		}
	}
	return 0;

}