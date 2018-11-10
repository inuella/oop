//Genre.h
#pragma once
#include "Book.h"
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<Book *> Books;
typedef Books::iterator BIter;
typedef Books::const_iterator CBIter;
 
class Genre
{
    const int gnum;
    string name;
    Books books;
    static const int max_book;
public:
    Genre(int gnum,string name);
    ~Genre(void);
    void View()const;
    Book *AddBook(string isbn);
    int GetGNum()const;
    void ViewAll()const;
    void FindBook()const;
    string RemoveBook();
};

