//App.h
#pragma once
#include "Genre.h"
#include <list>
#include <map>
using namespace std;

typedef list<Genre *> Genres;
typedef Genres::iterator GIter;
typedef Genres::const_iterator CGIter;

typedef map<string, Book *> BookDic;
typedef BookDic::iterator BDIter;
typedef BookDic::const_iterator CBDIter;


class App
{
    Genres genres;
    BookDic bookdic;
    int last_gnum;
public:
    App(void);
    ~App(void);
    void Run();
private:
    int SelectMenu();//메뉴 출력 및 선택    
    void AddGenre(); //장르 추가
    void ListGenre(); //전체 장르 보기
    void AddBook();  //도서 추가
    void RemoveBook(); //도서 삭제
    void FindBookByISBN(); //ISBN으로 도서 검색
    void FindBookAtAGenre(); //특정 장르 선택 후 도서 검색
    void ViewAGenre(); //특정 장르 보기
    void ListBook(); //전체 도서 보기
    void ViewAll(); //전체 보기

    Genre *SelectGenre();//장르 선택
};

