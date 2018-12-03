#pragma once


#include <string>
#include <vector>
#include "User.h"


using namespace std;

class Item{

private:
	string name;    


public:
	Item();
	string getName();

	void setName(string newName);


};