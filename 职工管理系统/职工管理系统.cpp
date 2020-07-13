#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using namespace std;


//void test()
//{
//	Worker* worker = NULL;
//	worker = new Employee(1, "����", 1);
//	worker->showInfo();
//	delete worker;
//
//	worker = new Manager(2, "����", 2);
//	worker->showInfo();
//	delete worker;
//
//	worker = new Boss(3, "����", 3);
//	worker->showInfo();
//	delete worker;
//}


int main() {
	workerManager wm;
	
	int choice = 0;
	while (true) {
		wm.Show_Menu();
		cin >> choice;
		switch (choice) {
		case 0: // �˳�ϵͳ
			wm.exitSystem();
			break;
		case 1: // ���ְ��
			wm.addEmp();
			break;
		case 2: // ��ʾְ��
			wm.show_Emp();
			break;
		case 3:// ɾ��ְ��
			wm.del_Emp();
			break;
		case 4: // �޸�ְ��
			wm.mod_Emp();
			break;
		case 5: // ����ְ��
			wm.find_Emp();
			break;
		case 6: // ����ְ��
			wm.sort_Emp();
			break;
		case 7: // ����ļ�
			wm.clean_File();
			break;
		}
	}

	system("pause");
	return 0;


}