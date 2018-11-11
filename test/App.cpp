//App.cpp
#include "App.h"

void App::Run() {
	int key = NO_DEFINED;
	while ((key = SelectMenu()) != ESC) {//�޴� ��� �� ����
		switch (key) {
		case F1: AddBook(); break; //���� �߰�
		case F2: RemoveBook(); break; //���� ����
		case F3: ViewAll(); break; //��ü ����
		case F4: ViewAGenre(); break; //Ư�� �帣 ����
		case F5: FindBook(); break; //���� �˻�
		case F6: RentBook(); break; //���� ������
		case F7: ReturnBook(); break; //���� �ݳ�
		case F8: ViewAll(); break; //��ü ����
		default: cout << "�߸� �����ϼ̽��ϴ�." << endl; break;
		}
		cout << "�ƹ� Ű�� ��������." << endl;
		ehglobal::getkey();
	}

	int App::SelectMenu() {//�޴� ��� �� ����    ��������
		ehglobal::clrscr();
		cout << "���� ���� ���α׷� [ESC]����" << endl;
		cout << "F1: ���� �߰�" << endl << " F2: ���� ����" << endl;
		cout << "F3:��ü ���� ����" << endl << " F4:�帣�� ���� ����" << endl;
		cout << "F5: �������� ���� �˻�" << endl;
		cout << "F6: ���� ����" << endl;
		cout << "F7: ���� �ݳ�" << endl;
		cout << "F8: ��ü ���� ����" << endl;

		return ehglobal::getkey();
	}

	void App::AddBook() {//���� �߰�
		cout << "�߰��� ������ ����:";
		string isbn = ehglobal::getstr();
		if (bookdic[isbn])
		{
			cout << "�̹� �ִ� ������ �����Դϴ�." << endl;
			return;
		}
		Book *book = genre->AddBook(isbn);
		if (book)
		{
			bookdic[isbn] = book;
		}
	}

	void App::RemoveBook() {//���� ����
		Genre *genre = SelectGenre();
		if (genre == 0)
		{
			cout << "�߸� �����Ͽ����ϴ�." << endl;
			return;
		}
		string isbn = genre->RemoveBook();
		bookdic[isbn] = 0;
	}
}