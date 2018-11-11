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
	int SelectMenu();//�޴� ��� �� ����    
	void AddBook(); //���� �߰�
	void RemoveBook(); //���� ����
	void FindBook(); //���� �˻�
	void ViewAGenre(); //Ư�� �帣 ����
	void RentBook(); //���� ����
	void ReturnBook(); //���� �ݳ�
	void ViewAll(); //��ü ����

	Genre *SelectGenre();//�帣 ����
};

