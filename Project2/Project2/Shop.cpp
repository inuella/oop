
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// �뿩�� Ŭ����.
#include "Shop.h"
#include <time.h>

string Shop::timeCheck() {
	time_t now;
	time(&now);
	string s; // ���� �� �� ����ð� ����
	s = asctime(localtime(&now));
	string str1 = s.substr(4, 3); // ��
	string str2 = s.substr(8, 2); // ��
	string str3 = s.substr(11, 2); // ��
	string str4 = s.substr(20, 4); // ����
	str1 = monthChange(str1);
	return str4 + "�� " + str1 + "�� " + str2 + "�� " + str3 + "�� ";
}


string Shop::monthChange(string mon) {
	if (mon == "Jan") {
		return "01";
	}
	else if (mon == "Feb") {
		return "02";
	}
	else if (mon == "Mar") {
		return "03";
	}
	else if (mon == "Apr") {
		return "04";
	}
	else if (mon == "May") {
		return "05";
	}
	else if (mon == "Jun") {
		return "06";
	}
	else if (mon == "Jul") {
		return "07";
	}
	else if (mon == "Aug") {
		return "08";
	}
	else if (mon == "Sep") {
		return "09";
	}
	else if (mon == "Oct") {
		return "10";
	}
	else if (mon == "Nov") {
		return "11";
	}
	else if (mon == "Dec") {
		return "12";
	}
	else return "";
}


Shop::Shop()
{}

	

Shop::~Shop(){}

