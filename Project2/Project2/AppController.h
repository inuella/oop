#pragma once
#include "Librarian.h"

class AppController {

private:
	void MenuTitle(const char* s);

	int InputMenu(int max);

	int Menu();

	int InputNumber();

public:

	void run();
};