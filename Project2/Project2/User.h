

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
	string name;      // 이름
	string birth;     // 생년월일
	string phone;     // 전화번호
	string address;   // 주소

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

	// 유저 정보 출력.
	friend ostream& operator<<(ostream& o, User& user)
	{
		o << user.getName() << "\t" << user.getBirth() << "\t";
		o << user.getPhone() << "\t" << user.getAddress() << "\t";
		return o;
	}
};

#endif;