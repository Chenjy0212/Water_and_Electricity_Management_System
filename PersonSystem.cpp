#include"PersonSystem.h"
#include"Student.h"
#include"Person.h"
#include <iostream>

personsystem::personsystem() {

	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//文件不存在的情况
	if (!ifs.is_open()) {
		this->m_num = 0;      //初始化人数
		this->m_file = true;  //初始化文件为空标志
		this->m_arr = NULL;   //初始化数组
		ifs.close();          //关闭文件
		return;
	}
	//文件存在,数据为空
	char ch;
	ifs >> ch;  //读字符
	if (ifs.eof()) {
		this->m_num = 0;
		this->m_file = true;
		this->m_arr = NULL;
		ifs.close();
		return;
	}
	//文件存在，且数据不为空
	int num = this->get_num();
	this->m_num = num;
	//开辟空间
	this->m_arr = new person * [this->m_num];
	//将文件中的数据存到数组中
	this->in_stu();
}
personsystem::~personsystem() {
	if (this->m_arr != NULL) {
		delete[]this->m_arr;
		this->m_arr = NULL;
	}//释放堆区的数据
}
void personsystem::m_save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//将每个人的数据写进文件中
	for (int i = 0; i < this->m_num; i++)
	{
		ofs << this->m_arr[i]->m_name << " "
			<< this->m_arr[i]->m_id << " "
			<< this->m_arr[i]->m_roomNumber << " "
			<< this->m_arr[i]->m_UID << endl;
	}
	ofs.close();
}
//统计文件中的人数
int personsystem::get_num() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	int id;
	int roomnum;
	int UID;

	int num = 0;
	while (ifs >> name && ifs >> id && ifs >> roomnum && ifs >> UID) {
		num++;
	}
	ifs.close();
	return num;
}
//获取文件中的编号
vector<int> personsystem::get_id() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	int id;
	int roomnum;
	int UID;

	vector<int> idv;
	while (ifs >> name && ifs >> id && ifs >> roomnum && ifs >> UID) {
		idv.push_back(id);
	}
	ifs.close();
	return idv;
}
void personsystem::in_stu() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	int roomNumber;
	string name;
	int UID;

	int index = 0;
	while (ifs >> name && ifs >> id && ifs >> roomNumber && ifs >> UID) {
		person* person = NULL;
		if (UID == 1) {
			person = new teacher(name, id, roomNumber, UID);
		}
		else {
			person = new student(name, id, roomNumber, UID);
		}

		this->m_arr[index] = person;
		index++;
	}
}

//显示信息
void personsystem::show_stu() {
	if (this->m_file) {
		cout << "文件为空" << endl;
	}
	else {
		cout << "当前用户总人数为： " << this->get_num() << endl;
		for (int i = 0; i < m_num; i++) {
			this->m_arr[i]->show_info();
			cout << endl;

		}
	}
	system("pause");
	system("cls");
}

//添加信息
void personsystem::add_info() {
	cout << "请输入你要添加的人数" << endl;
	int addnum = 0;
	cin >> addnum;

	if (addnum > 0) {
		int newsize = this->m_num + addnum;          //计算新空间大小
		person** newspace = new person * [newsize];  //在堆区开辟新空间
		if (this->m_arr != NULL)                     //将原空间下内容放到新空间下
		{
			for (int i = 0; i < this->m_num; i++)
			{
				newspace[i] = this->m_arr[i];
			}
		}

		vector<int> idv = this->get_id();  //获取所有输入的编号
		//for (auto i : idv) {
		//	cout << i << endl;
		//}
		for (int i = 0; i < addnum; i++) {
			int id;
			string name;
			int roomNumber;
			int num;

			cout << "请输入第" << i + 1 << "个人的名字" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个人的学工号" << endl;
			cin >> id;
			auto it = find(idv.begin(), idv.end(), id);
			while (it != idv.end()) {
				cout << "学工号已存在，请重新输入" << endl;
				cin >> id;
				it = find(idv.begin(), idv.end(), id);
			}
			cout << "请输入第" << i + 1 << "个人的房间号" << endl;
			cin >> roomNumber;
			cout << "请选择你的身份，老师输入1，学生输入2" << endl;
			cin >> num;
			while (num != 1 && num != 2) {
				cout << "输入有误，请重新输入" << endl;
				cin >> num;
			}
			person* person = NULL;
			switch (num) {
			case 1:
				person = new student(name, id, roomNumber, 1);
				break;
			case 2:
				person = new teacher(name, id, roomNumber, 2);
				break;
			default:
				break;
			}

			newspace[this->m_num + i] = person;
		}
		delete[]this->m_arr;//释放原来的空间
		this->m_arr = newspace;//更改新空间的指向
		this->m_num = newsize;//更改新的个数
		this->m_file = false;//更新职工不为空标志
		cout << "成功添加" << endl;
		this->m_save();
	}
	else {
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}
//判断是否存在
int personsystem::is_exist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_num; i++) {
		if (this->m_arr[i]->m_id == id) {
			index = i;
			break;
		}
	}
	return index;
}
int personsystem::is_exist2(int roomNumber) {
	int index = -1;
	for (int i = 0; i < this->m_num; i++) {
		if (this->m_arr[i]->m_roomNumber == roomNumber) {
			index = i;
			break;
		}
	}
	return index;
}
//删除信息
void personsystem::del_info() {
	if (this->m_file) {
		cout << "文件不存在" << endl;
	}
	else {
		cout << "请输入想删除的人的编号" << endl;
		int id;
		cin >> id;

		int index = this->is_exist(id);
		if (index != -1) {
			for (int i = index; i < this->m_num - 1; i++) {
				this->m_arr[i] = this->m_arr[i + 1];
			}
			this->m_num--;//更新数组中记录个数
			//同步到文件中
			this->m_save();
			cout << "删除成功" << endl;
		}
		else {
			cout << "删除失败，未找到该人" << endl;
		}
	}
	system("pause");
	system("cls");
}
//修改信息
void personsystem::mod_info() {
	if (this->m_file) {
		cout << "文件不存在" << endl;
	}
	else {
		cout << "请输入编号" << endl;
		int id;
		cin >> id;

		int ret = this->is_exist(id);
		if (ret != -1) {
			delete this->m_arr[ret];
			int new_id = 0;
			string new_name;
			int new_roomNumber;
			int new_UID;
			cout << "请输入你的名字" << endl;
			cin >> new_id;
			cout << "请输入你的ID" << endl;
			cin >> new_name;
			cout << "请输入你的房间号" << endl;
			cin >> new_roomNumber;
			cout << "请选择你的身份，老师输入1，学生输入2" << endl;
			cin >> new_UID;
			person* person = NULL;
			switch (new_UID) {
			case 1:
				person = new student(new_name, new_id, new_roomNumber, 1);
				break;
			case 2:
				person = new teacher(new_name, new_id, new_roomNumber, 2);
				break;
			default:
				break;
			}
			this->m_arr[ret] = person;
			cout << "修改成功" << endl;
			this->m_save();

		}
		else {
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}
void personsystem::exitsystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(5);
}
void personsystem::menu2() {
	cout << "欢迎使用用户信息管理系统" << endl;
	cout << "******1，添加信息******" << endl;
	cout << "******2，删除信息******" << endl;
	cout << "******3，修改信息******" << endl;
	cout << "******4，显示信息******" << endl;
	cout << "******5，返回主菜单****" << endl;
	cout << endl;
}