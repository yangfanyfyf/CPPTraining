#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

workerManager::workerManager() {
	// 文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	// 文件存在但是没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空!" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	
	this->m_EmpNum = num;  //更新成员属性 
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	init_Emp();

	/*for (int i = 0; i < m_EmpNum; i++)
	{
		cout << "职工号： " << this->m_EmpArray[i]->m_Id
			<< " 职工姓名： " << this->m_EmpArray[i]->m_Name
			<< " 部门编号： " << this->m_EmpArray[i]->m_DeptId << endl;
	}*/


}

workerManager::~workerManager() {
	if (this->m_EmpArray != NULL) {
		delete[] this->m_EmpArray;
	}
}

void workerManager::Show_Menu() {
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
	cout << "请输入您的选择：" << endl;
}


// 5. 退出功能
void workerManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}


// 7. 添加职工，m_empNum是人数，m_EmpArray初始化数组指针
// 数组的长度会变化
void workerManager::addEmp() {
	cout << "请输入增加职工数量：" << endl;

	int addNum = 0;

	//需要增加的人数
	cin >> addNum;
	if (addNum > 0) {
		// 用int有时候会报错！！！！！！！！
		int newSize = this->m_EmpNum + addNum; // 新的总人数
		// 开辟新的空间
		Worker** newSpace = new Worker * [newSize];

		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];  // 将原来的内容放到新的空间中
			}
		}
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;

			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
			cin >> name;
			cout << "请选择该职工的岗位：" << endl;
			cout << "1. 普通职工" << endl;
			cout << "2. 经理" << endl;
			cout << "3. 老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;

			switch (dSelect) {
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker; // 警告？
		}

		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize; // 更新
		cout << "成功添加" << addNum << "名新职工" << endl;

		this->save();
	}
	else {
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");

}

void workerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	// 内存错误？
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			  << this->m_EmpArray[i]->m_Name << " "
			  << this->m_EmpArray[i]->m_DeptId << endl;

	}
	ofs.close();
}

int workerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		num++;
	}
	ifs.close();

	return num;
}


void workerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker * worker = NULL;
		if (dId == 1) {
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {
			worker = new Manager(id, name, dId);
		}
		else {
			worker = new Boss(id, name, dId);
		}

		this->m_EmpArray[index] = worker;
		index++;
	}
}

void workerManager::show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		for (int i = 0; i != this->m_EmpNum; ++i) {
			this->m_EmpArray[i]->showInfo(); // 是employee 的一个函数
		}
	}
	system("pause");
	system("cls");
}

// 删除时需要判断是否存在这个人
int workerManager::is_Exist(int id) {
	int index = -1;
	for (int i = 0; i != this->m_EmpNum; ++i) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}

void workerManager::del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入想要删除的职工号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->is_Exist(id);
		if (index != -1) {
			for (int i = index; i != this->m_EmpNum - 1; ++i) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1]; // 直接前移覆盖
			}
			this->m_EmpNum--;
			this->save();
			cout << "删除成功！" << endl;
		}
		else {
			cout << "删除失败，未找到该职工。" << endl;
		}
	}
	system("pause");
	system("cls");
}




// 有时候会保存时会出错，为什么？
void workerManager::mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入修改的职工编号" << endl;
		int id;
		cin >> id;
		int ret = this->is_Exist(id); // 返回的ret已经是顺序

		if (ret != -1) {
			delete this->m_EmpArray[ret];
			//this->m_EmpArray[ret] = NULL;

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查找到：" << id << "号职工，请输入新职工编号：" << endl;
			cin >> newId;

			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请输入岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker *worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			this->m_EmpArray[ret] = worker;
			
			this->save(); //会报错

			cout << "修改成功" << endl;
		}
		else {
			cout << "查无此人" << endl;
		}
	}

	system("pause");
	system("cls");
}


void workerManager::find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者记录为空" << endl;
	}
	else {
		cout << "请输入查找的方式：" << endl;
		cout << "1. 按照职工编号查找" << endl;
		cout << "2. 按照姓名查找" << endl;
		int waySearch;
		cin >> waySearch;

		if (waySearch == 1) {
			cout << "请输入查找的职工编号：" << endl;
			int id;
			cin >> id;
			int index = is_Exist(id);
			if (index != -1) {
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else {
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if(waySearch == 2){
			cout << "请输入查找的姓名：" << endl;
			string name = "";
			cin >> name;
			bool flag = false;
			for (int i = 0; i != m_EmpNum; ++i) {
				if (m_EmpArray[i]->m_Name == name) {
					cout << "查找成功，职工编号为" << m_EmpArray[i]->m_Id << "号的信息如下：" << endl;
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false) {
				cout << "查找失败，查无此人" << endl;
			}
		}
		else {
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者记录为空" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序方式：" << endl;
		cout << "1. 按职工号进行升序" << endl;
		cout << "2. 按职工号进行降序" << endl;
		int waySort;
		cin >> waySort;

		for (int i = 0; i != m_EmpNum; ++i) {
			int min_or_max = i;
			for (int j = i + 1; j != m_EmpNum; ++j) {
				if (waySort == 1) {
					if (m_EmpArray[min_or_max]->m_Id > m_EmpArray[j]->m_Id) {
						min_or_max = j; // 从小到大
					}
				}
				else if(waySort == 2){
					if (m_EmpArray[min_or_max]->m_Id < m_EmpArray[j]->m_Id) {
						min_or_max = j; 
					}
				}
				else{
					cout << "输入有误" << endl;
					system("pause");
					system("cls");
					return;
				}
			}
			if (i != min_or_max) {
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[min_or_max];
				m_EmpArray[min_or_max] = temp;
			}
		}
		cout << "排序成功，排序后结果为：" << endl;
		this->save();
		this->show_Emp();
	}
}

void workerManager::clean_File() {
	cout << "确认清空？" << endl;
	cout << "1. 确认" << endl;
	cout << "2. 返回" << endl;

	int realClean;
	cin >> realClean;

	if (realClean == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL) {
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}