#pragma once
#include <iostream>
#include "worker.h"
#include <fstream>
#define FILENAME "empFile.txt"

using namespace std;

class workerManager {
public:
	workerManager();

	void Show_Menu();
	
	void exitSystem();

	void addEmp();

	void save();

	int get_EmpNum();

	void init_Emp();

	void show_Emp();

	void del_Emp();

	int is_Exist(int id);
	
	void mod_Emp();

	void find_Emp();

	void sort_Emp();

	void clean_File();

	~workerManager();

	int m_EmpNum;
	Worker ** m_EmpArray;
	bool m_FileIsEmpty;
};

