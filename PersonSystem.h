#pragma once
#include<iostream>
#include<string>
#include"Student.h"
#include"Teacher.h"
#include<fstream>
#include <vector>
#define FILENAME "persontable.txt"
using namespace std;

class personsystem
{
public:
	personsystem();

	void m_save();  // 储存信息
	bool m_file;    //文件是否存在
	int get_num();  //获取人数
	vector<int> get_id();  //获取id

	void in_stu();

	int m_num;
	person** m_arr;
	//显示菜单
	void menu2();
	int is_exist(int id);  //判断是否存在
	int is_exist2(int roomNumber);
	void show_stu();       //显示信息
	void add_info();       //添加信息
	void mod_info();       //修改信息
	void del_info();       //删除信息
	void exitsystem();     //退出系统

	~personsystem();
};