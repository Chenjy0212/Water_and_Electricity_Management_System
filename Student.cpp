#include"Student.h"

student::student(string name, int id, int roomNumber, int UID) {
	this->m_name = name;
	this->m_id = id;
	this->m_roomNumber = roomNumber;
	this->m_UID = UID;
}
void student::show_info() {
	cout << "姓名：" << m_name << endl;
	cout << "学号：" << m_id << endl;
	cout << "房间号：" << m_roomNumber << endl;
	cout << "身份：" << this->get_name() << endl;
}
string student::get_name()
{
	return string("学生");
}

stucoststd::stucoststd(double usage, int type) {
	this->c_usage = usage;
	this->c_type = type;
}
double stucoststd::cal_price() {
	double price = 0;
	// 如果是用电
	if (c_type == 1) {
		if (c_usage <= 50) {
			return price;
		}
		else {
			return ((c_usage - 50) * 1.2);
		}
	}
	// 如果是用水
	else if (c_type == 2) {
		if (c_usage <= 50) {
			return price;
		}
		else {
			return ((c_usage - 50) * 0.5);
		}
	}
}