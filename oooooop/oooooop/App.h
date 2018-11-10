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
    int SelectMenu();//�޴� ��� �� ����    
    void AddGenre(); //�帣 �߰�
    void ListGenre(); //��ü �帣 ����
    void AddBook();  //���� �߰�
    void RemoveBook(); //���� ����
    void FindBookByISBN(); //ISBN���� ���� �˻�
    void FindBookAtAGenre(); //Ư�� �帣 ���� �� ���� �˻�
    void ViewAGenre(); //Ư�� �帣 ����
    void ListBook(); //��ü ���� ����
    void ViewAll(); //��ü ����

    Genre *SelectGenre();//�帣 ����
};

