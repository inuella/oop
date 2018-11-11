//Genre.cpp
#include "Genre.h"

const int Genre::max_book = 100;
Genre::Genre(int gnum,string name):gnum(gnum)
{
    this->name = name;
    books.resize(max_book,0);
}


Genre::~Genre(void)
{
    for(int index=0; index<max_book;++index)
    {
        if(books[index])
        {
            delete books[index];
        }
    }
}

void Genre::View()const
{
    cout<<"No."<<gnum<<" , 장르 이름:"<<name<<endl;
}
Book *Genre::AddBook(string isbn)
{
    cout<<"장르 내 도서 구분자(1~100):";
    int bnum = ehglobal::getnum();
    if((bnum<1)||(bnum>100))
    {
        cout<<"범위를 벗어난 도서 구분자입니다."<<endl;
        return 0;
    }
    cout<<"도서 제목:";
    string title = ehglobal::getstr();

    books[bnum-1] =new Book(isbn,bnum,title);
    return books[bnum-1];
}
int Genre::GetGNum()const
{
    return gnum;
}
void Genre::ViewAll()const
{
    View();
    for(int index=0; index<max_book;++index)
    {
        if(books[index])
        {
            books[index]->View();
        }
    }
}
void Genre::FindBook()const
{
    cout<<"장르 내 도서 구분자(1~100):";
    int bnum = ehglobal::getnum();
    if((bnum<1)||(bnum>100))
    {
        cout<<"범위를 벗어난 도서 구분자입니다."<<endl;        
        return;
    }
    
    if(books[bnum-1])
    {
        books[bnum-1]->View();
    }
    else
    {
        cout<<"없는 도서입니다."<<endl;
    }
}
string Genre::RemoveBook()
{
    cout<<"장르 내 도서 구분자(1~100):";
    int bnum = ehglobal::getnum();
    if((bnum<1)||(bnum>100))
    {
        cout<<"범위를 벗어난 도서 구분자입니다."<<endl;        
        return "";
    }
    
    if(books[bnum-1])
    {
        string isbn = books[bnum-1]->GetISBN();
        delete books[bnum-1];
        books[bnum-1] = 0;
        return isbn;
    }
    cout<<"없는 도서입니다."<<endl;
    return "";
}