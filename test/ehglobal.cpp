//ehglobal.cpp
#include "ehglobal.h"

void ehglobal::clrscr()//ȭ���� ����� �޼���
{
    system("cls");
}

void ehglobal::timeflow(int millisecond) //���ϴ� �ð����� ������Ű�� �޼���
{
    Sleep(millisecond);
}

int ehglobal::getnum()//������ �Է¹޴� �޼���
{
    int num;
    char buf[255+1];
    cin.getline(buf,255);
    cin.clear();
    sscanf(buf,"%d",&num);
    return num;
}


string ehglobal::getstr()//���ڿ��� �Է¹޴� �޼���
{
    char buf[255+1];
    cin.getline(buf,255);
    cin.clear();
    return buf;
}

int ehglobal::getkey()//��� Ű�� �Է¹޴� �޼���
{
    int key = getch();

    if(key == 27) //ESC�� ���� ���� key ���� 27��
    {
        return ESC;
    }
    if(key == 0) //��� Ű�� ������ ���� getch�� ��ȯ���� 0��
    {
        //� ��� Ű�� �������� Ȯ���Ϸ��� getch�� �ٽ� ȣ���ؾ� ��
        //����ڿ��� �ٽ� Ű�� �Է¹޴� ���� �ƴ�
        key = getch();
        switch(key) //�Է��� Ű�� ���� ��ӵ� �� ��ȯ
        {
        case 59: return F1;    case 60: return F2;
        case 61: return F3;    case 62: return F4;
        case 63: return F5;    case 64: return F6;
        case 65: return F7;    case 66: return F8;
        case 67: return F9;    case 68: return F10;
        }
    }
    return NO_DEFINED; //���ŵ��� ���� Ű�� ������ ��
}
