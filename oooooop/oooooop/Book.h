//Book.h
#pragma once
#include "ehglobal.h"
class Book
{
    const string isbn;
    int bnum;
    string title;
public:
    Book(string isbn,int bnum,string title);    
    void View()const;
    string GetISBN()const;
};

