#include <iostream>
#include "speechManager.h"
#include "speaker.h"
using namespace std;

int main() {
	speechManager sm;

	int choice = 0;

	while (true) {
		sm.showMenu();
		cout << "����������ѡ��" << endl;
		cin >> choice;

		switch (choice) {
		case 1:  //��ʼ����
			sm.startSpeech();
			break;
		case 2:  //�鿴��¼
			
			break;
		case 3:  //��ռ�¼
			break;
		case 0:  //�˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls"); //����
			break;
		}
	}

}