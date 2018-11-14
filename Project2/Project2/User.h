

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

public:
	User() { };

	string getName();
	string getBirth();
	string getPhone();
	string getAddress();

	void setName(string newName);
	void setBirth(string newBirth);
	void setPhone(string newPhone);
	void setAddress(string newAddress);

	// ���� ���� ���.
	friend ostream& operator<<(ostream& o, User& user)
	{
		o << user.getName() << "\t" << user.getBirth() << "\t";
		o << user.getPhone() << "\t" << user.getAddress() << "\t";
		return o;
	}
};

#endif;