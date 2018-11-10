//Book.cpp
#include "Book.h"


Book:: Book(string isbn,int bnum,string title):isbn(isbn)
{
    this->bnum = bnum;
    this->title = title;
}
void Book::View()const
{
    cout<<isbn<<" ,No."<<bnum<<", Á¦¸ñ:"<<title<<endl;
}
string Book::GetISBN()const
{
    return isbn;
}