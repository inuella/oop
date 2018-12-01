

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
	cout << "****** 도 서 관 리 프 로 그 램 *********" << endl;
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
		cout << "잘못 입력하셨습니다. 다시 입력해 주세요 (0~" << max << ") : ";
	}
	return menu;
}

int AppController::InputNumber() {
	int num;
	while (true) {
		cin >> num;
		if (num >= 1 && num <= 2) return num;
		cout << "잘못 입력하셨습니다. 다시 입력해 주세요 (1~2) : ";
		
	}

}

int AppController::Menu() {
	int menu;
	int num;
	Librarian librarian;

	while (1) {
		cout << "도서관리 프로그램" << endl;
		cout << "1. 대여" << endl;
		cout << "2. 반납" << endl;
		cout << "3. 대여현황" << endl;
		cout << "4. 유저관리" << endl;
		cout << "5. 관리" << endl;
		cout << "6. (관리자전용) 대여불가 해제" << endl;
		cout << "0. 돌아가기" << endl;
		cout << "> ";
		menu = InputMenu(6);

		switch (menu)
		{
		case 1:
			cout << "대여" << endl;
			cout << "1번을 입력하면 도서, 2번을 입력하면 DVD를 대여합니다." << endl;
			num = InputNumber();
			librarian.Rent(num);
			break;
		case 2:
			cout << "반납" << endl;
			cout << "1번을 입력하면 도서, 2번을 입력하면 DVD를 반납합니다." << endl;
			num = InputNumber();
			librarian.Return(num);
			break;
		case 3:
			cout << "대여현황" << endl;
			librarian.RentList();
			break;
		case 4:
			cout << "유저관리" << endl;
			cout << "1. 유저등록" << endl;
			cout << "2. 유저검색" << endl;
			cout << "3. 유저목록" << endl;
			cout << "0. 돌아가기" << endl;
			cout << "> ";
			menu = InputMenu(3);
			switch (menu)
			{
			case 1:
				cout << "유저등록" << endl;
				librarian.AddUser();
				break;
			case 2:
				cout << "유저검색" << endl;
				librarian.FindUser();
				break;
			case 3:
				cout << "유저목록" << endl;
				librarian .UserList();
				break;
			case 0:
				break;
			}
			break;
		case 5:
			cout << "관리" << endl;
			cout << "1. 등록" << endl;
			cout << "2. 검색" << endl;
			cout << "3. 목록" << endl;
			cout << "0. 돌아가기" << endl;
			cout << "> ";
			menu = InputMenu(3);
			switch (menu)
			{
			case 1:
				cout << "등록" << endl;
				cout << "1번을 입력하면 도서, 2번을 입력하면 DVD를 등록합니다." << endl;
				num = InputNumber();
				librarian.Add(num);
				break;
			case 2:
				cout << "검색" << endl;
				cout << "1번을 입력하면 도서, 2번을 입력하면 DVD를 검색합니다." << endl;
				num = InputNumber();
				librarian.Find(num);
				break;
			case 3:
				cout << "목록" << endl;
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