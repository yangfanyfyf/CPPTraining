#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

workerManager::workerManager() {
	// �ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	// �ļ����ڵ���û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��!" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	
	this->m_EmpNum = num;  //���³�Ա���� 
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	init_Emp();

	/*for (int i = 0; i < m_EmpNum; i++)
	{
		cout << "ְ���ţ� " << this->m_EmpArray[i]->m_Id
			<< " ְ�������� " << this->m_EmpArray[i]->m_Name
			<< " ���ű�ţ� " << this->m_EmpArray[i]->m_DeptId << endl;
	}*/


}

workerManager::~workerManager() {
	if (this->m_EmpArray != NULL) {
		delete[] this->m_EmpArray;
	}
}

void workerManager::Show_Menu() {
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
	cout << "����������ѡ��" << endl;
}


// 5. �˳�����
void workerManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}


// 7. ���ְ����m_empNum��������m_EmpArray��ʼ������ָ��
// ����ĳ��Ȼ�仯
void workerManager::addEmp() {
	cout << "����������ְ��������" << endl;

	int addNum = 0;

	//��Ҫ���ӵ�����
	cin >> addNum;
	if (addNum > 0) {
		// ��int��ʱ��ᱨ����������������
		int newSize = this->m_EmpNum + addNum; // �µ�������
		// �����µĿռ�
		Worker** newSpace = new Worker * [newSize];

		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];  // ��ԭ�������ݷŵ��µĿռ���
			}
		}
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;

			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ������" << endl;
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1. ��ְͨ��" << endl;
			cout << "2. ����" << endl;
			cout << "3. �ϰ�" << endl;
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
			newSpace[this->m_EmpNum + i] = worker; // ���棿
		}

		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize; // ����
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

		this->save();
	}
	else {
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");

}

void workerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	// �ڴ����
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i != this->m_EmpNum; ++i) {
			this->m_EmpArray[i]->showInfo(); // ��employee ��һ������
		}
	}
	system("pause");
	system("cls");
}

// ɾ��ʱ��Ҫ�ж��Ƿ���������
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		cout << "��������Ҫɾ����ְ���ţ�" << endl;
		int id = 0;
		cin >> id;
		int index = this->is_Exist(id);
		if (index != -1) {
			for (int i = index; i != this->m_EmpNum - 1; ++i) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1]; // ֱ��ǰ�Ƹ���
			}
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
		}
	}
	system("pause");
	system("cls");
}




// ��ʱ��ᱣ��ʱ�����Ϊʲô��
void workerManager::mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		cout << "�������޸ĵ�ְ�����" << endl;
		int id;
		cin >> id;
		int ret = this->is_Exist(id); // ���ص�ret�Ѿ���˳��

		if (ret != -1) {
			delete this->m_EmpArray[ret];
			//this->m_EmpArray[ret] = NULL;

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "���ҵ���" << id << "��ְ������������ְ����ţ�" << endl;
			cin >> newId;

			cout << "��������������" << endl;
			cin >> newName;

			cout << "�������λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			
			this->save(); //�ᱨ��

			cout << "�޸ĳɹ�" << endl;
		}
		else {
			cout << "���޴���" << endl;
		}
	}

	system("pause");
	system("cls");
}


void workerManager::find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1. ����ְ����Ų���" << endl;
		cout << "2. ������������" << endl;
		int waySearch;
		cin >> waySearch;

		if (waySearch == 1) {
			cout << "��������ҵ�ְ����ţ�" << endl;
			int id;
			cin >> id;
			int index = is_Exist(id);
			if (index != -1) {
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if(waySearch == 2){
			cout << "��������ҵ�������" << endl;
			string name = "";
			cin >> name;
			bool flag = false;
			for (int i = 0; i != m_EmpNum; ++i) {
				if (m_EmpArray[i]->m_Name == name) {
					cout << "���ҳɹ���ְ�����Ϊ" << m_EmpArray[i]->m_Id << "�ŵ���Ϣ���£�" << endl;
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false) {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else {
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "��ѡ������ʽ��" << endl;
		cout << "1. ��ְ���Ž�������" << endl;
		cout << "2. ��ְ���Ž��н���" << endl;
		int waySort;
		cin >> waySort;

		for (int i = 0; i != m_EmpNum; ++i) {
			int min_or_max = i;
			for (int j = i + 1; j != m_EmpNum; ++j) {
				if (waySort == 1) {
					if (m_EmpArray[min_or_max]->m_Id > m_EmpArray[j]->m_Id) {
						min_or_max = j; // ��С����
					}
				}
				else if(waySort == 2){
					if (m_EmpArray[min_or_max]->m_Id < m_EmpArray[j]->m_Id) {
						min_or_max = j; 
					}
				}
				else{
					cout << "��������" << endl;
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
		cout << "����ɹ����������Ϊ��" << endl;
		this->save();
		this->show_Emp();
	}
}

void workerManager::clean_File() {
	cout << "ȷ����գ�" << endl;
	cout << "1. ȷ��" << endl;
	cout << "2. ����" << endl;

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
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}