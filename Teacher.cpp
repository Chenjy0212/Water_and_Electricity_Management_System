#include"Teacher.h"

teacher::teacher(string name, int id, int roomNumber, int UID) {
	this->m_name = name;
	this->m_id = id;
	this->m_roomNumber = roomNumber;
	this->m_UID = UID;
}
void teacher::show_info() {
	cout << "姓名：" << m_name << endl;
	cout << "学号：" << m_id << endl;
	cout << "房间号：" << m_roomNumber << endl;
	cout << "身份：" << this->get_name() << endl;
}
string teacher::get_name()
{
	return string("老师");
}

teccoststd::teccoststd(double usage, int type) {
	this->c_usage = usage;
	this->c_type = type;
}
double teccoststd::cal_price() {
	// 如果是用电
	if (c_type == 1) {
		return (c_usage * 0.8);
	}
	// 如果是用水
	else if (c_type == 2) {
		return (c_usage * 0.3);
	}
}