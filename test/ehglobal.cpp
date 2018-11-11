//ehglobal.cpp
#include "ehglobal.h"

void ehglobal::clrscr()//화면을 지우는 메서드
{
    system("cls");
}

void ehglobal::timeflow(int millisecond) //원하는 시간동안 지연시키는 메서드
{
    Sleep(millisecond);
}

int ehglobal::getnum()//정수를 입력받는 메서드
{
    int num;
    char buf[255+1];
    cin.getline(buf,255);
    cin.clear();
    sscanf(buf,"%d",&num);
    return num;
}


string ehglobal::getstr()//문자열을 입력받는 메서드
{
    char buf[255+1];
    cin.getline(buf,255);
    cin.clear();
    return buf;
}

int ehglobal::getkey()//기능 키를 입력받는 메서드
{
    int key = getch();

    if(key == 27) //ESC를 누를 때의 key 값이 27임
    {
        return ESC;
    }
    if(key == 0) //기능 키를 눌렀을 때는 getch의 반환값이 0임
    {
        //어떤 기능 키를 눌렀는지 확인하려면 getch를 다시 호출해야 함
        //사용자에게 다시 키를 입력받는 것은 아님
        key = getch();
        switch(key) //입력한 키에 따라 약속된 값 반환
        {
        case 59: return F1;    case 60: return F2;
        case 61: return F3;    case 62: return F4;
        case 63: return F5;    case 64: return F6;
        case 65: return F7;    case 66: return F8;
        case 67: return F9;    case 68: return F10;
        }
    }
    return NO_DEFINED; //열거되지 않은 키를 눌렀을 때
}
