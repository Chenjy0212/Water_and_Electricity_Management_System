#include"usingwater.h"

usingwater::usingwater(int id, int roomnum, string ltime, string time, double ldegree, double degree, double price, int type, bool pay) {
	this->s_id = id;
	this->s_roomnum = roomnum;
	this->s_ltime = ltime;
	this->s_time = time;
	this->s_ldegree = ldegree;
	this->s_degree = degree;
	this->s_price = price;
	this->s_type = type;
	this->s_pay = pay;
}

//void usingwater::show_info00() {
//	cout << "编号：" << s_id << endl;
//	cout << "类型：" << get_type() << endl;
//	cout << "房间号：" << s_roomnum << endl;
//	cout << "上次抄表时间：" << timeformat(s_ltime) << endl;
//	cout << "本次抄表时间：" << timeformat(s_time) << endl;
//	cout << "上次抄表度数：" << s_ldegree << endl;
//	cout << "本次抄表度数：" << s_degree << endl;
//	cout << "价格：" << s_price << endl;
//	if (s_pay) {
//		cout << "已支付" << endl;
//	}
//	else {
//		cout << "未支付" << endl;
//	}
//}
//
//string usingwater::get_type() {
//	if (s_type == 1) return string("电表");
//	else return string("水表");
//}