

#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <string>



using namespace std;

class User
{
private:
	string name;      // 이름
	string birth;     // 생년월일
	string phone;     // 전화번호
	string address;   // 주소
	string dueDate;
	string availability;


public:
	User() { };

	string getName();
	string getBirth();
	string getPhone();
	string getAddress();
	string getDueDate();
	string getAvailability();


	void setName(string newName);
	void setBirth(string newBirth);
	void setPhone(string newPhone);
	void setAddress(string newAddress);
	void setDueDate(string newDueDate);
	void setAvailability(string newAvailability);

};

#endif;