#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
#include "Book.h"
#include "BookShop.h"

using namespace std;




// 메뉴 타이틀 및 카테고리 출력 함수.
void MenuTitle(const char* s)
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

	MenuTitle("");


	while (1)
	{
		cout << "메뉴" << endl;
		cout << "1. 도서대여" << endl;
		cout << "2. 도서반납" << endl;
		cout << "3. 대여현황" << endl;
		cout << "4. 유저관리" << endl;
		cout << "5. 도서관리" << endl;
		cout << "6. 추천도서" << endl;
		cout << "0. 종료" << endl;
		cout << "> ";
		menu = InputMenu(6);

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
			cout << "2. 유저검색" << endl;
			cout << "3. 유저목록" << endl;
			cout << "0. 돌아가기" << endl;
			cout << "> ";
			menu = InputMenu(3);
			switch (menu)
			{
			case 1:
				cout << "유저등록" << endl;
				bookshop.AddUser();
				break;
			case 2:
				cout << "유저검색" << endl;
				bookshop.FindUser();
				break;
			case 3:
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
		case 6:
			cout << "  추천 도서입니다." << endl;
			bookshop.RandomBook();
			break;
		case 0:
			return 0;
		}
	}
	return 0;
}