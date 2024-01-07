#pragma once
#include<iostream>
#include<string>
#include"UsingElectricity.h"
#include"UsingWater.h"
#include<fstream>
#define FILENAME1 "wetable.txt"
using namespace std;

class usingsystem
{
public:
	usingsystem();

	void m_save();  //储存信息
	bool m_file;    //文件是否存在
	int get_num();  //获取数量
	void in_stu();

	int m_num;
	system1** m_arr1;

	void menu1();//显示菜单
	int is_exist(int id);//判断是否存在
	void show_stu();//显示信息
	void add_info();//添加信息
	void sear_price();//查询费用
	void sear_info();//查询缴费记录
	void not_pay();//查询未缴费名单
	void exitsystem();//退出系统

	~usingsystem();
};