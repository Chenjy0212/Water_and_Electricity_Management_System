#pragma once
#include<iostream>
#include<string>
#include <iomanip>
using namespace std;

class system1
{
public:
	int s_id;              // 订单号
	int s_roomnum;         // 房号
	string s_ltime;         // 上次抄表时间
	string s_time;         // 本次抄表时间
	double s_ldegree;       // 上次抄表度数
	double s_degree;       // 本次抄表度数
	double s_price;        // 价格
	int s_type;            // 水表还是电表
	bool s_pay;            // 是否已缴费

	void show_info00() {
		cout << "编号：" << s_id << endl;
		cout << "类型：" << get_type() << endl;
		cout << "房间号：" << s_roomnum << endl;
		cout << "上次抄表时间：" << timeformat(s_ltime) << endl;
		cout << "本次抄表时间：" << timeformat(s_time) << endl;
		cout << "上次抄表度数：" << fixed << setprecision(2) << s_ldegree << get_unit() << endl;
		cout << "本次抄表度数：" << fixed << setprecision(2) << s_degree << get_unit()<< endl;
		cout << "价格：" << fixed << setprecision(2) << s_price << "￥" << endl;
		cout << "支付状态：";
		if (s_pay) {
			cout << "已支付" << endl;
		}
		else {
			cout << "未支付" << endl;
		}
	}
	string get_type() {
		if (s_type == 1) return string("电表");
		else return string("水表");
	}
	string timeformat(string time) {
		if (time.length() != 8) return "格式有误，请参考输入：2020101。当前为：" + time;
		else return time.substr(0, 4) + "年" + time.substr(4, 2) + "月" + time.substr(6, 2) + "日";
	}
	string get_unit() {
		switch (s_type)
		{
		case 1:
			return "千瓦时";
			break;
		case 2:
			return "立方米";
			break;
		default:
			return "Error 格式有误！请检查";
			break;
		}
		if (s_type == 1) return string("电表");
		else return string("水表");
	}

	void show_find_room_res() {
		cout << "编号：" << s_id << endl;
		cout << "类型：" << get_type() << endl;
		cout << "使用周期：" << timeformat(s_ltime) << " - " << timeformat(s_time) << endl;
		cout << "使用总量:" << fixed << setprecision(2) << (s_degree - s_ldegree) <<get_unit() << endl;
		cout << "应付价格：" << fixed << setprecision(2) << s_price << "￥" << endl;
		cout << "支付状态：";
		if (s_pay) {
			cout << "已支付" << endl;
		}
		else {
			cout << "未支付" << endl;
		}
	}

	void show_table() {
		cout << "|" << setw(7) << s_id << setw(8) << "|" << setw(16) << timeformat(s_ltime) << setw(3) << "|"  << setw(15) << timeformat(s_time) << setw(2) << "|" << setw(8) << s_degree - s_ldegree << setw(3) << "|" << setw(9) << s_price << setw(4) <<  "|" << endl;
	}
};