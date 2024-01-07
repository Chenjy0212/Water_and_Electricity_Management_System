#pragma once
#include<iostream>
#include<string>
#include"UsingElectricity.h"
#include"UsingWater.h"
#include<fstream>
#define FILENAME1 "wetable.txt"
#include <ctime>
#include <map>

#include <time.h>
//线程不安全处理
#pragma warning( disable : 4996 )
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

	vector<int> get_time() {
		// 获取当前时间的time_t类型值
		time_t now = time(0);

		// 将time_t转换为tm结构体表示的本地时间
		tm* localTime = localtime(&now);

		// 输出年、月、日、小时、分钟和秒
		vector<int> mytime;
		mytime.push_back(localTime->tm_year + 1900);
		mytime.push_back(localTime->tm_mon + 1);
		mytime.push_back(localTime->tm_mday);
		mytime.push_back(localTime->tm_hour);
		mytime.push_back(localTime->tm_min);
		mytime.push_back(localTime->tm_sec);

		return mytime;
	}
	string vtos(vector<int> vec) {
		string res= "";
		//年
		res += to_string(vec[0]);
		//月 日 时 分 秒
		for (int i = 1; i < 6; i++) {
			if (to_string(vec[i]).length() != 2) res += "0" + to_string(vec[i]);
			else res += to_string(vec[i]);
		}
		
		return res;
	}
	void time_format2(vector<int> timevec) {
		cout << timevec[0] << "年" \
			<< timevec[1] << "月" \
			<< timevec[2] << "日" \
			<< timevec[3] << "时" \
			<< timevec[4] << "分" \
			<< timevec[5] << "秒" << endl;
	}
};