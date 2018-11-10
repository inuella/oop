//ehglobal.h
#pragma once
#pragma warning(disable:4996)
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::cin;
using std::ostream;
using std::endl;
#include <conio.h>
#include <windows.h>
enum keydata
{
    NO_DEFINED,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,ESC
};

//공통적으로 사용할 정적 메서드를 캡슐화한 클래스
class ehglobal
{
public:
    static void clrscr();//화면을 지우는 메서드
    static void timeflow(int millisecond); //원하는 시간동안 지연시키는 메서드
    static int getnum();//정수를 입력받는 메서드
    static string getstr();//문자열을 입력받는 메서드
    static int getkey();//기능 키를 입력받는 메서드
private:
    ehglobal(void){ }//개체를 생성하지 못하게 하기 위해 private으로 접근 지정
    ~ehglobal(void){}
};
