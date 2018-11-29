

#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <string>



using namespace std;

class User
{
	friend class BookShop;
private:
	string name;      // �̸�
	string birth;     // �������
	string phone;     // ��ȭ��ȣ
	string address;   // �ּ�
	string dueDate;

public:
	User() { };

	string getName();
	string getBirth();
	string getPhone();
	string getAddress();
	string getDueDate();

	void setName(string newName);
	void setBirth(string newBirth);
	void setPhone(string newPhone);
	void setAddress(string newAddress);
	void setDueDate(string newDueDate);

	// ���� ���� ���.
	friend ostream& operator<<(ostream& o, User& user)
	{
		o << user.getName() << "\t" << user.getBirth() << "\t";
		o << user.getPhone() << "\t" << user.getAddress() << "\t" << user.getDueDate() << "\t";
		return o;
	}
};

#endif;