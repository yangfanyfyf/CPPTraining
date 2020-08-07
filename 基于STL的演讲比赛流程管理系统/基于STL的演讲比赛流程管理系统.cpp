#include <iostream>
#include "speechManager.h"
#include "speaker.h"
using namespace std;

int main() {
	speechManager sm;

	int choice = 0;

	while (true) {
		sm.showMenu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice) {
		case 1:  //开始比赛
			sm.startSpeech();
			break;
		case 2:  //查看记录
			
			break;
		case 3:  //清空记录
			break;
		case 0:  //退出系统
			sm.exitSystem();
			break;
		default:
			system("cls"); //清屏
			break;
		}
	}

}