

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "AppController.h"

using namespace std;

void AppController::MenuTitle(const char* s)
{
	system("cls");
	cout << "****************************************" << endl;
	cout << "****** �� �� �� �� �� �� �� �� *********" << endl;
	cout << "****************************************" << endl;
	cout << s << endl;
}

int AppController::InputMenu(int max)
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

int AppController::InputNumber() {
	int num;
	while (true) {
		cin >> num;
		if (num >= 1 && num <= 2) return num;
		cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ��� (1~2) : ";
		
	}

}

int AppController::Menu() {
	int menu;
	int num;
	Librarian librarian;

	while (1) {
		cout << "�������� ���α׷�" << endl;
		cout << "1. �뿩" << endl;
		cout << "2. �ݳ�" << endl;
		cout << "3. �뿩��Ȳ" << endl;
		cout << "4. ��������" << endl;
		cout << "5. ����" << endl;
		cout << "6. (����������) �뿩�Ұ� ����" << endl;
		cout << "0. ���ư���" << endl;
		cout << "> ";
		menu = InputMenu(6);

		switch (menu)
		{
		case 1:
			cout << "�뿩" << endl;
			cout << "1���� �Է��ϸ� ����, 2���� �Է��ϸ� DVD�� �뿩�մϴ�." << endl;
			num = InputNumber();
			librarian.Rent(num);
			break;
		case 2:
			cout << "�ݳ�" << endl;
			cout << "1���� �Է��ϸ� ����, 2���� �Է��ϸ� DVD�� �ݳ��մϴ�." << endl;
			num = InputNumber();
			librarian.Return(num);
			break;
		case 3:
			cout << "�뿩��Ȳ" << endl;
			librarian.RentList();
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
				librarian.AddUser();
				break;
			case 2:
				cout << "�����˻�" << endl;
				librarian.FindUser();
				break;
			case 3:
				cout << "�������" << endl;
				librarian .UserList();
				break;
			case 0:
				break;
			}
			break;
		case 5:
			cout << "����" << endl;
			cout << "1. ���" << endl;
			cout << "2. �˻�" << endl;
			cout << "3. ���" << endl;
			cout << "0. ���ư���" << endl;
			cout << "> ";
			menu = InputMenu(3);
			switch (menu)
			{
			case 1:
				cout << "���" << endl;
				cout << "1���� �Է��ϸ� ����, 2���� �Է��ϸ� DVD�� ����մϴ�." << endl;
				num = InputNumber();
				librarian.Add(num);
				break;
			case 2:
				cout << "�˻�" << endl;
				cout << "1���� �Է��ϸ� ����, 2���� �Է��ϸ� DVD�� �˻��մϴ�." << endl;
				num = InputNumber();
				librarian.Find(num);
				break;
			case 3:
				cout << "���" << endl;
				librarian.List();
				break;
			case 0:
				break;
			}
			break;

		case 6:
			librarian.recoverAvailability();
			break;

		case 0:
			return 0;
		}

	}
	return 0;
}





void AppController::run()
{

	MenuTitle("");

	Menu();

}