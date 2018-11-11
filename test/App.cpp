//App.cpp
#include "App.h"

void App::Run() {
	int key = NO_DEFINED;
	while ((key = SelectMenu()) != ESC) {//메뉴 출력 및 선택
		switch (key) {
		case F1: AddBook(); break; //도서 추가
		case F2: RemoveBook(); break; //도서 삭제
		case F3: ViewAll(); break; //전체 보기
		case F4: ViewAGenre(); break; //특정 장르 보기
		case F5: FindBook(); break; //도서 검색
		case F6: RentBook(); break; //도서 빌리기
		case F7: ReturnBook(); break; //도서 반납
		case F8: ViewAll(); break; //전체 보기
		default: cout << "잘못 선택하셨습니다." << endl; break;
		}
		cout << "아무 키나 누르세요." << endl;
		ehglobal::getkey();
	}

	int App::SelectMenu() {//메뉴 출력 및 선택    ㅊㅊㅇㅇ
		ehglobal::clrscr();
		cout << "도서 관리 프로그램 [ESC]종료" << endl;
		cout << "F1: 도서 추가" << endl << " F2: 도서 삭제" << endl;
		cout << "F3:전체 도서 보기" << endl << " F4:장르별 도서 보기" << endl;
		cout << "F5: 제목으로 도서 검색" << endl;
		cout << "F6: 도서 대출" << endl;
		cout << "F7: 도서 반납" << endl;
		cout << "F8: 전체 도서 보기" << endl;

		return ehglobal::getkey();
	}

	void App::AddBook() {//도서 추가
		cout << "추가할 도서의 제목:";
		string isbn = ehglobal::getstr();
		if (bookdic[isbn])
		{
			cout << "이미 있는 도서의 제목입니다." << endl;
			return;
		}
		Book *book = genre->AddBook(isbn);
		if (book)
		{
			bookdic[isbn] = book;
		}
	}

	void App::RemoveBook() {//도서 삭제
		Genre *genre = SelectGenre();
		if (genre == 0)
		{
			cout << "잘못 선택하였습니다." << endl;
			return;
		}
		string isbn = genre->RemoveBook();
		bookdic[isbn] = 0;
	}
}