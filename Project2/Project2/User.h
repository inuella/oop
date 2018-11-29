

#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <string>



using namespace std;

class User
{
private:
	string name;      // �̸�
	string birth;     // �������
	string phone;     // ��ȭ��ȣ
	string address;   // �ּ�
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