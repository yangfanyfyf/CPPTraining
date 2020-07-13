#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker {
public:
	virtual void showInfo() = 0;

	virtual string getDeptName() = 0;
	// 纯虚函数，只能被继承，不能被实例化
	int m_Id;
	string m_Name;
	int m_DeptId;
};