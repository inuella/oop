#pragma once
#include "Code.h"
#include <list>
#include <map>
using namespace std;

typedef list<Code *> Codes;
typedef Codes::iterator CIter;
typedef Codes::const_iterator CCIter;

typedef map<string, Book *> BookDic;
typedef BookDic::iterator BDIter;
typedef BookDic::const_iterator CBDIter;


class App
{
	Codes codes;
	BookDic bookdic;
	int last_cnum;
public:
	App(void);
	void Run();
private:
	int SelectMenu();//메뉴 출력 및 선택    
	void AddBook(); //도서 추가
	void RemoveBook(); //도서 삭제
	void FindBook(); //도서 검색
	void ViewAGenre(); //특정 장르 보기
	void RentBook(); //도서 대출
	void ReturnBook(); //도서 반납
	void ViewAll(); //전체 보기

	Genre *SelectGenre();//장르 선택
};

