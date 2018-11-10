//App.cpp
#include "App.h"

App::App(void)
{
    last_gnum = 0;
}
App::~App(void)
{
    //�帣 �Ҹ�
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
    while((key = SelectMenu())!=ESC)//�޴� ��� �� ����
    {
        switch(key)
        {
        case F1: AddGenre(); break;//�帣 �߰�
        case F2: ListGenre(); break; //��ü �帣 ����
        case F3: AddBook(); break; //���� �߰�
        case F4: RemoveBook(); break; //���� ����
        case F5: FindBookByISBN(); break; //ISBN���� ���� �˻�
        case F6: FindBookAtAGenre(); break; //Ư�� �帣 ���� �� ���� �˻�
        case F7: ViewAGenre(); break; //Ư�� �帣 ����
        case F8: ListBook(); break; //��ü ���� ����
        case F9: ViewAll(); break; //��ü ����
        default: cout<<"�߸� �����ϼ̽��ϴ�."<<endl; break;
        }
        cout<<"�ƹ� Ű�� ��������."<<endl;
        ehglobal::getkey();
    }
}

int App::SelectMenu()//�޴� ��� �� ����    ��������
{
    ehglobal::clrscr();
    cout<<"�帣�� ���� ���� ���α׷� [ESC]����"<<endl;
    cout<<"F1: �帣 �߰� F2:��ü �帣 ����"<<endl;
    cout<<"F3: ���� �߰� F4: ���� ����"<<endl;
    cout<<"F5: ISBN���� ���� �˻�"<<endl;
    cout<<"F6: Ư�� �帣 ���� �� ���� �˻�"<<endl;
    cout<<"F7: Ư�� �帣 ����"<<endl;
    cout<<"F8: ��ü ���� ���� F9: ��ü ����"<<endl;

    return ehglobal::getkey();
}
void App::AddGenre() //�帣 �߰�
{
    last_gnum++;
    cout<<last_gnum<<"��° �߰��� �帣 �̸�:"<<endl;
    string gname = ehglobal::getstr();
    genres.push_back(new Genre(last_gnum,gname));
}
void App::ListGenre() //��ü �帣 ����
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
void App::AddBook()  //���� �߰�
{
    cout<<"�߰��� ������ ISBN:";
    string isbn = ehglobal::getstr();
    if(bookdic[isbn])
    {
        cout<<"�̹� �ִ� ������ ISBN�Դϴ�."<<endl;
        return;
    }
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"�߸� �����Ͽ����ϴ�."<<endl;
        return;
    }
    Book *book = genre->AddBook(isbn);
    if(book)
    {
        bookdic[isbn] = book;
    }
}
Genre *App::SelectGenre()//�帣 ����
{
    ListGenre();
    cout<<"������ �帣 ��ȣ:";
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
void App::RemoveBook() //���� ����
{
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"�߸� �����Ͽ����ϴ�."<<endl;
        return;
    }
    string isbn = genre->RemoveBook();
    bookdic[isbn] = 0;   
}
void App::FindBookByISBN() //ISBN���� ���� �˻�
{
    cout<<"�˻��� ������ ISBN:";
    string isbn = ehglobal::getstr();
    if(bookdic[isbn]==0)
    {
        cout<<"���� ������ ISBN�Դϴ�."<<endl;
        return;
    }
    bookdic[isbn]->View();
}
void App::FindBookAtAGenre() //Ư�� �帣 ���� �� ���� �˻�
{
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"�߸� �����Ͽ����ϴ�."<<endl;
        return;
    }
    genre->FindBook();
}
void App::ViewAGenre() //Ư�� �帣 ����
{
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"�߸� �����Ͽ����ϴ�."<<endl;
        return;
    }
    genre->ViewAll();
}
void App::ListBook() //��ü ���� ����
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
void App::ViewAll() //��ü ����
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
