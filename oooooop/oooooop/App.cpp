//App.cpp
#include "App.h"

App::App(void)
{
    last_gnum = 0;
}
App::~App(void)
{
    //장르 소멸
    GIter seek = genres.begin();
    GIter last = genres.end();
    Genre *genre = 0;
    for(   ;seek != last ; ++seek)
    {
        genre = *seek;
        delete genre;
    }
}

void App::Run()
{
    int key=NO_DEFINED;
    while((key = SelectMenu())!=ESC)//메뉴 출력 및 선택
    {
        switch(key)
        {
        case F1: AddGenre(); break;//장르 추가
        case F2: ListGenre(); break; //전체 장르 보기
        case F3: AddBook(); break; //도서 추가
        case F4: RemoveBook(); break; //도서 삭제
        case F5: FindBookByISBN(); break; //ISBN으로 도서 검색
        case F6: FindBookAtAGenre(); break; //특정 장르 선택 후 도서 검색
        case F7: ViewAGenre(); break; //특정 장르 보기
        case F8: ListBook(); break; //전체 도서 보기
        case F9: ViewAll(); break; //전체 보기
        default: cout<<"잘못 선택하셨습니다."<<endl; break;
        }
        cout<<"아무 키나 누르세요."<<endl;
        ehglobal::getkey();
    }
}

int App::SelectMenu()//메뉴 출력 및 선택    ㅊㅊㅇㅇ
{
    ehglobal::clrscr();
    cout<<"장르별 도서 관리 프로그램 [ESC]종료"<<endl;
    cout<<"F1: 장르 추가 F2:전체 장르 보기"<<endl;
    cout<<"F3: 도서 추가 F4: 도서 삭제"<<endl;
    cout<<"F5: ISBN으로 도서 검색"<<endl;
    cout<<"F6: 특정 장르 선택 후 도서 검색"<<endl;
    cout<<"F7: 특정 장르 보기"<<endl;
    cout<<"F8: 전체 도서 보기 F9: 전체 보기"<<endl;

    return ehglobal::getkey();
}
void App::AddGenre() //장르 추가
{
    last_gnum++;
    cout<<last_gnum<<"번째 추가할 장르 이름:"<<endl;
    string gname = ehglobal::getstr();
    genres.push_back(new Genre(last_gnum,gname));
}
void App::ListGenre() //전체 장르 보기
{
    GIter seek = genres.begin();
    GIter last = genres.end();
    Genre *genre = 0;
    for(   ;seek != last ; ++seek)
    {
        genre = *seek;
        genre->View();
    }
}
void App::AddBook()  //도서 추가
{
    cout<<"추가할 도서의 ISBN:";
    string isbn = ehglobal::getstr();
    if(bookdic[isbn])
    {
        cout<<"이미 있는 도서의 ISBN입니다."<<endl;
        return;
    }
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"잘못 선택하였습니다."<<endl;
        return;
    }
    Book *book = genre->AddBook(isbn);
    if(book)
    {
        bookdic[isbn] = book;
    }
}
Genre *App::SelectGenre()//장르 선택
{
    ListGenre();
    cout<<"선택할 장르 번호:";
    int gnum = ehglobal::getnum();
    
    
    GIter seek = genres.begin();
    GIter last = genres.end();
    Genre *genre = 0;
    for(   ;seek != last ; ++seek)
    {
        genre = *seek;
        if(genre->GetGNum() == gnum)
        {
            return genre;
        }
    }
    return 0;
}
void App::RemoveBook() //도서 삭제
{
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"잘못 선택하였습니다."<<endl;
        return;
    }
    string isbn = genre->RemoveBook();
    bookdic[isbn] = 0;   
}
void App::FindBookByISBN() //ISBN으로 도서 검색
{
    cout<<"검색할 도서의 ISBN:";
    string isbn = ehglobal::getstr();
    if(bookdic[isbn]==0)
    {
        cout<<"없는 도서의 ISBN입니다."<<endl;
        return;
    }
    bookdic[isbn]->View();
}
void App::FindBookAtAGenre() //특정 장르 선택 후 도서 검색
{
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"잘못 선택하였습니다."<<endl;
        return;
    }
    genre->FindBook();
}
void App::ViewAGenre() //특정 장르 보기
{
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"잘못 선택하였습니다."<<endl;
        return;
    }
    genre->ViewAll();
}
void App::ListBook() //전체 도서 보기
{
    BDIter seek = bookdic.begin();
    BDIter last = bookdic.end();
    Book *book=0;
    for(  ;seek != last; ++seek)
    {
        book = (*seek).second;
        if(book)
        {
            book->View();
        }
    }
}
void App::ViewAll() //전체 보기
{
    GIter seek = genres.begin();
    GIter last = genres.end();
    Genre *genre = 0;
    for(   ;seek != last ; ++seek)
    {
        genre = *seek;
        genre->ViewAll();
    }    
}
