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

//���������� ����� ���� �޼��带 ĸ��ȭ�� Ŭ����
class ehglobal
{
public:
    static void clrscr();//ȭ���� ����� �޼���
    static void timeflow(int millisecond); //���ϴ� �ð����� ������Ű�� �޼���
    static int getnum();//������ �Է¹޴� �޼���
    static string getstr();//���ڿ��� �Է¹޴� �޼���
    static int getkey();//��� Ű�� �Է¹޴� �޼���
private:
    ehglobal(void){ }//��ü�� �������� ���ϰ� �ϱ� ���� private���� ���� ����
    ~ehglobal(void){}
};
