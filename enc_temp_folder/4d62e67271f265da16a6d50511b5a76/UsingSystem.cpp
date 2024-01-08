#include"UsingElectricity.h"
#include"PersonSystem.h"
#include"UsingSystem.h"
#include"UsingWater.h"
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

int g_var1 = 0;

// 根据需求返回最大的日期或者最小的日期。
string compareDate(vector<string>datavec, string type) {

	if (datavec.size() == 0)
		throw "日期内容为空";
	if (datavec[0].length() != 8 && datavec[0].length() != 12)
		throw "日期格式有误";
	for (int i = 1; i < datavec.size(); i++) {
		if (datavec[0].length() != datavec[i].length()) {
			throw "日期格式有误";
		}
	}

	string maxd = datavec[0];
	string mind = datavec[0];

	for (int i = 1; i < datavec.size(); i++) {
		for (int j = 0; j < datavec[i].length(); j++) {
			if (datavec[i][j] > maxd[j]) {
				maxd = datavec[i];
				break;
			}
			if (datavec[i][j] < mind[j]) {
				mind = datavec[i];
				break;
			}
		}
	}

	if (type == "max") {
		return maxd;
	}
	else if (type == "min") {
		return mind;
	}
}
// 获取半年前的时间
string get6month_ago(string data) {
	if (data.length() != 12 && data.length() != 8) {
		throw "时间格式不正确";
	}
	if (data.length() == 12) {
		data = data.substr(0, 8);
	}
#	//介于 7 - 9月
	int mon = stoi(data.substr(4, 2));
	if (mon >= 7 && mon < 10) {
		mon -= 6;
		data[5] = mon + '0';
	}
	// 大于等于10月
	else if (mon >= 10) {
		mon -= 6;
		data[4] = '0';
		data[5] = mon + '0';
	}
	//小于 7 月
	else {
		int year = stoi(data.substr(0, 4));
		year -= 1;
		int mon = stoi(data.substr(4, 2));
		//小于等于6月大于3月
		if (mon >3 && mon <= 6) {
			mon += 6 - 10;
			data[4] = '1';
			data[5] = mon + '0';
		}
		// 小于等于3月
		else if (mon <= 3) {
			mon += 6;
			data[5] = mon + '0';
		}
		data = to_string(year) + data.substr(4, 4);
	}

	return data;
}
// 判断日期是否在半年内
bool in6mon(string date, string dateago) {
	bool res = false;
	for (int i = 0; i < 8; i++) {
		if (date[i] > dateago[i]) {
			res = true;
			break;
		}
	}
	return res;
}

usingsystem::usingsystem() {
	ifstream ifs;
	ifs.open(FILENAME1, ios::in);
	//文件不存在的情况
	if (!ifs.is_open()) {
		this->m_num = 0;//初始化数量
		this->m_file = true;//初始化文件为空标志
		this->m_arr1 = NULL;//初始化数组
		ifs.close();//关闭文件
		return;
	}
	//文件存在,数据为空
	char ch;
	ifs >> ch;//读字符
	if (ifs.eof()) {
		this->m_num = 0;
		this->m_file = true;
		this->m_arr1 = NULL;
		ifs.close();
		return;
	}
	//文件存在，且数据不为空
	int num = this->get_num();
	this->m_num = num;
	//开辟空间
	this->m_arr1 = new system1 * [this->m_num];
	//将文件中的数据存到数组中
	this->in_stu();
	//订单号自动续上
	g_var1 = this->m_arr1[this->m_num - 1]->s_id;
}
usingsystem::~usingsystem() {
	if (this->m_arr1 != NULL) {
		delete[]this->m_arr1;
		this->m_arr1 = NULL;
	}//释放堆区的数据
}
void usingsystem::m_save() {
	ofstream ofs;
	ofs.open(FILENAME1, ios::out);
	//将数据写进文件中
	for (int i = 0; i < this->m_num; i++)
	{
		ofs << this->m_arr1[i]->s_id << " "
			<< this->m_arr1[i]->s_roomnum << " "
			<< this->m_arr1[i]->s_ltime << " "
			<< this->m_arr1[i]->s_time << " "
			<< this->m_arr1[i]->s_ldegree << " "
			<< this->m_arr1[i]->s_degree << " "
			<< this->m_arr1[i]->s_price << " "
			<< this->m_arr1[i]->s_type << " "  
			<< this->m_arr1[i]->s_pay << " "
			<< this->m_arr1[i]->s_paytime << endl;
	}
	ofs.close();
}
//统计文件记录数据的数目
int usingsystem::get_num() {
	ifstream ifs;
	ifs.open(FILENAME1, ios::in);

	int id;
	int roomnum;
	string ltime;
	string time;
	double ldegree;
	double degree;
	double price;
	int type;
	bool pay;
	string paytime;

	int num = 0;
	while (ifs >> id && ifs >> roomnum && ifs >> ltime && ifs >> time && ifs >> ldegree && ifs >> degree && ifs >> price && ifs >> type && ifs >> pay && ifs >> paytime) {
		num++;
	}
	ifs.close();
	return num;
}
void usingsystem::in_stu() {
	ifstream ifs;
	ifs.open(FILENAME1, ios::in);
	int id;
	int roomnum;
	string ltime;
	string time;
	double ldegree;
	double degree;
	double price;
	int type;
	bool pay;
	string paytime;

	int index = 0;
	while (ifs >> id && ifs >> roomnum && ifs >> ltime && ifs >> time && ifs >> ldegree && ifs >> degree && ifs >> price && ifs >> type && ifs >> pay && ifs >> paytime) {
		system1* system = NULL;
		if (type == 1) {
			system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay, paytime);
		}
		if (type == 2) {
			system = new usingwater(id, roomnum, ltime, time, ldegree, degree, price, 2, pay, paytime);
		}
		this->m_arr1[index] = system;
		index++;
	}
}

//显示所有信息
void usingsystem::show_stu() {
	// 和表的数据同步
	this->in_stu();
	if (this->m_file) {
		cout << "文件为空" << endl;
	}
	else {
		for (int i = 0; i < this->m_num; i++) {
			this->m_arr1[i]->show_info00();
			cout << endl;
		}
		cout << "当前用水用电记录总共有 " << this->get_num() << " 条" << endl;
	}
	system("pause");
	system("cls");
}
//添加信息
void usingsystem::add_info() {
	personsystem s;

	int newsize = this->m_num + 1;//计算新空间大小
	system1** newspace1 = new system1 * [newsize];//在堆区开辟新空间
	if (this->m_arr1 != NULL) //将原空间下内容放到新空间下
	{
		for (int i = 0; i < this->m_num; i++)
		{
			newspace1[i] = this->m_arr1[i];
		}
	}
	//循环多次输入会导致数据的写入延迟，没必要保留
	int id;
	int roomnum;
	string time;
	string ltime = "20240101";
	double degree;
	double ldegree = 0;
	double price;
	bool pay = false;
	string paytime = "########";

	id = ++g_var1;
	cout << "请输入房间号：" << endl;
	cin >> roomnum;
	int ret = s.is_exist2(roomnum);
	int quit_flag = 0;
	while (ret == -1) {
		cout << "房间号不正确，请重新输入" << endl;
		cin >> roomnum;
		ret = s.is_exist2(roomnum);
		// 避免输入错误陷入死讯黄
		++quit_flag;
		if (quit_flag == 10) break;
	}
	cout << "请输入当前的抄表时间(eg：20240101)" << endl;
	cin >> time;
	cout << "电表请输入1，水表请输入2" << endl;
	int num;
	cin >> num;
	while (num != 1 && num != 2) {
		cout << "Error！输入有误。电表输入1，水表输入2" << endl;
		cin >> num;
	}
	switch (num)
	{
	case 1:
		cout << "请输入当前用电表度数" << endl;
		break;
	case 2:
		cout << "请输入当前水表使用数" << endl;
		break;
	}
	cin >> degree;

	// 自动获取上次记录时间和使用的量
	bool exite_flag = false;
	vector<string> datavec;
	for (int i = 0; i < this->m_num; i++)
	{
		// 如果之前有记录的话
		if (this->m_arr1[i]->s_roomnum == roomnum && this->m_arr1[i]->s_type == num) {
			//根据是不同的表有不同的结果
			exite_flag = true;
			ldegree = max(m_arr1[i]->s_degree, ldegree);
			datavec.push_back(this->m_arr1[i]->s_time);
			//ltime = to_string(static_cast<int>(max(ceilf(stof(this->m_arr1[i]->s_time)), stof(ltime))));
		}
	}
	ltime = compareDate(datavec, "max");

	if (!exite_flag){ // 如果没有记录,那么初始化，且设定为已经支付，因为没有前后使用量为0
		ldegree = degree;
		ltime = time;
		pay = true;
	}

	system1* system1 = NULL;
	switch (num) {
	case 1: {
		if(s.m_arr[ret]->m_UID == 1){
			stucoststd* scs = new stucoststd(degree - ldegree, num);
			price = scs->cal_price();
			delete scs;
			system1 = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay, paytime);
			break;
		}
		else {
			teccoststd* tcs = new teccoststd(degree - ldegree, num);
			price = tcs->cal_price();
			delete tcs;
			system1 = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay, paytime);
			break;
		}
	}
	case 2: {
		if (s.m_arr[ret]->m_UID == 1) {
			stucoststd* scs = new stucoststd(degree - ldegree, num);
			price = scs->cal_price();
			delete scs;
			system1 = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 2, pay, paytime);
			break;
		}
		else {
			teccoststd* tcs = new teccoststd(degree - ldegree, num);
			price = tcs->cal_price();
			delete tcs;
			system1 = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 2, pay, paytime);
			break;
		}
	}
	}
	newspace1[this->m_num] = system1;
			
	
	delete[]this->m_arr1;      //释放原来的空间
	this->m_arr1 = newspace1;  //更改新空间的指向
	this->m_num = newsize;     //更改新的个数
	this->m_file = false;      //更新不为空标志
	cout << "成功添加" << endl;
	this->m_save();

	system("pause");
	system("cls");
}
//判断是否存在
int usingsystem::is_exist(int roomnum) {
	int index = -1;
	int a = this->m_num;
	for (int i = 0; i < this->m_num; i++) {
		if (this->m_arr1[i]->s_roomnum == roomnum) {
			index = i;
			break;
		}
	}
	return index;
}
//查询费用，缴费
void usingsystem::sear_price() {
	// 和表的数据同步
	this->in_stu();
	cout << "请输入你的房间号" << endl;
	int num;
	cin >> num;
	int ret;
	ret = is_exist(num);
	if (ret != -1) {
		cout << "查询全部费用请输入0，查询电费请输入1，查询水费请输入2" << endl;
		int a;
		cin >> a;
		while (a < 0 || a > 2) {
			cout << "Error！输入有误。查询全部费用请输入0，查询电费请输入1，查询水费请输入2" << endl;
			cin >> a;
		}
		int count = 0;
		int unpaid_count = 0;
		double due_payment = 0;
		double due_payment_part = 0;
		vector<int> id_list;
		vector<int> id_list_tmp;
		string tmp_num;
		char ypq;

		switch (a)
		{
		case 0:
			for (int i = 0; i < this->m_num; i++) {
				//判断是不是初始化数据，同一天记录且使用量一样且已经缴费
				if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay) continue;
				
				if (this->m_arr1[i]->s_roomnum == num) {
					++count;
					if (!this->m_arr1[i]->s_pay) {
						//统计总量
						++unpaid_count;
						//统计应缴费用
						due_payment += this->m_arr1[i]->s_price;
						//记录编号
						id_list.push_back(i);
					}
					this->m_arr1[i]->show_find_room_res();
					cout << endl;
				}
			}
			cout << "总共 " << count << " 笔订单, 未支付共有 " << unpaid_count << " 笔" << endl;
			cout << "应缴费总金额为：" << due_payment << " ￥" << endl;
			cout << "1. 全部支付：请输入“a or A”" << endl;
			cout << "2. 选择支付：请输入“p or P”,输入想要付款的编号后，输入“y or Y”确认" << endl;
			cout << "3. 取消支付: 请输入“q or Q”" << endl;
			char ypq;
			cin >> ypq;
			while (ypq != 'a' && ypq != 'A' && ypq != 'P' && ypq != 'p' && ypq != 'q' && ypq != 'Q') {
				cout << "Error！输入有误。全部支付请输入“a or A”；选择支付请输入“p or P”使用“y or Y”结束；取消支付请输入“q or Q”。" << endl;
				cin >> ypq;
			}

			switch (ypq)
			{
			case 'a':case 'A':
				for (const auto& item : id_list) {
					if (!this->m_arr1[item]->s_pay) {
						this->m_arr1[item]->s_paytime = this->vtos(this->get_time()); //未支付过的账单才需要更新付款的时间
					}
					this->m_arr1[item]->s_pay = true;
				}
				this->m_save();
				cout << "全部支付成功！！！成交金额为：" << due_payment << " ￥" << endl;
				cout << "交易时间为：";
				this->time_format2(this->get_time());
				break;
			case 'p':case 'P':
				cout << "请输入需要支付的编号 [ ";
				for (const auto& item : id_list) {
					cout << item + 1 << " ";
				}
				cout << "]" << endl;
				while (cin >> tmp_num) {
					if (tmp_num == "y" || tmp_num == "Y") break;
					
					auto it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					while (it == id_list.end()) {
						cout << "请输入正确的需要支付的订单编号" << endl;
						cout << "所有需要支付的订单编号：[ ";
						for (const auto& item : id_list) {
							cout << item + 1 << " ";
						}
						cout << "]" << endl;
						cin >> tmp_num;
						it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					}
					id_list_tmp.push_back(stoi(tmp_num) - 1);
				}
				for (const auto& item_tmp : id_list_tmp) {
					if (!this->m_arr1[item_tmp]->s_pay) {
						this->m_arr1[item_tmp]->s_paytime = this->vtos(this->get_time()); //未支付过的账单才需要更新付款的时间
					}
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "部分支付成功！！！成交金额为：" << due_payment_part << " ￥" << endl;
				cout << "交易时间为：";
				this->time_format2(this->get_time());
				break;
			case 'q':case 'Q':
				cout << "已取消支付！！！" << endl;
				break;
			} 
			break;
		case 1:
			for (int i = 0; i < this->m_num; i++) {
				if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay) continue;
				if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 1) {
					++count;
					if (!this->m_arr1[i]->s_pay) {
						++unpaid_count;
						due_payment += this->m_arr1[i]->s_price;
						id_list.push_back(i);
					}
					this->m_arr1[i]->show_find_room_res();
					cout << endl;
				}
			}
			cout << "总共 " << count << " 笔订单, 未支付共有 " << unpaid_count << " 笔" << endl;
			cout << "应缴费总金额为：" << due_payment << " ￥" << endl;
			cout << "1. 全部支付：请输入“a or A”" << endl;
			cout << "2. 选择支付：请输入“p or P”,输入想要付款的编号后，输入“y or Y”确认" << endl;
			cout << "3. 取消支付: 请输入“q or Q”" << endl;
			cin >> ypq;
			while (ypq != 'a' && ypq != 'A' && ypq != 'P' && ypq != 'p' && ypq != 'q' && ypq != 'Q') {
				cout << "Error！输入有误。全部支付请输入“a or A”；选择支付请输入“p or P”使用“y or Y”结束；取消支付请输入“q or Q”。" << endl;
				cin >> ypq;
			}
			switch (ypq)
			{
			case 'a':case 'A':
				for (const auto& item : id_list) {
					if (!this->m_arr1[item]->s_pay) {
						this->m_arr1[item]->s_paytime = this->vtos(this->get_time()); //未支付过的账单才需要更新付款的时间
					}
					this->m_arr1[item]->s_pay = true;
				}
				this->m_save();
				cout << "全部支付成功！！！成交金额为：" << due_payment << " ￥" << endl;
				cout << "交易时间为：";
				this->time_format2(this->get_time());
				break;
			case 'p':case 'P':
				cout << "请输入需要支付的编号 [ ";
				for (const auto& item : id_list) {
					cout << item + 1 << " ";
				}
				cout << "]" << endl;
				while (cin >> tmp_num) {
					if (tmp_num == "y" || tmp_num == "Y") break;
					auto it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					while (it == id_list.end()) {
						cout << "请输入正确的需要支付的订单编号" << endl;
						cout << "所有需要支付的订单编号：[ ";
						for (const auto& item : id_list) {
							cout << item + 1 << " ";
						}
						cout << "]" << endl;
						cin >> tmp_num;
						it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					}
					id_list_tmp.push_back(stoi(tmp_num) - 1);

				}
				for (const auto& item_tmp : id_list_tmp) {
					if (!this->m_arr1[item_tmp]->s_pay) {
						this->m_arr1[item_tmp]->s_paytime = this->vtos(this->get_time()); //未支付过的账单才需要更新付款的时间
					}
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "部分支付成功！！！成交金额为：" << due_payment_part << " ￥" << endl;
				cout << "交易时间为：";
				this->time_format2(this->get_time());
				break;
			case 'q':case 'Q':
				cout << "已取消支付！！！" << endl;
				break;
			}
			break;
		case 2:
			for (int i = 0; i < this->m_num; i++) {
				if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay) continue;
				if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 2) {
					++count;
					if (!this->m_arr1[i]->s_pay) {
						++unpaid_count;
						due_payment += this->m_arr1[i]->s_price;
						id_list.push_back(i);
					}
					this->m_arr1[i]->show_find_room_res();
					cout << endl;
				}
			}
			cout << "总共 " << count << " 笔订单, 未支付共有 " << unpaid_count << " 笔未支付" << endl;
			cout << "应缴费总金额为：" << due_payment << " ￥" << endl;
			cout << "1. 全部支付：请输入“a or A”" << endl;
			cout << "2. 选择支付：请输入“p or P”,输入想要付款的编号后，输入“y or Y”确认" << endl;
			cout << "3. 取消支付: 请输入“q or Q”" << endl;
			cin >> ypq;
			while (ypq != 'a' && ypq != 'A' && ypq != 'P' && ypq != 'p' && ypq != 'q' && ypq != 'Q') {
				cout << "Error！输入有误。全部支付请输入“a or A”；选择支付请输入“p or P”使用“y or Y”结束；取消支付请输入“q or Q”。" << endl;
				cin >> ypq;
			}
			switch (ypq)
			{
			case 'a':case 'A':
				for (const auto& item : id_list) {
					if (!this->m_arr1[item]->s_pay) {
						this->m_arr1[item]->s_paytime = this->vtos(this->get_time()); //未支付过的账单才需要更新付款的时间
					}
					this->m_arr1[item]->s_pay = true;
				}
				this->m_save();
				cout << "全部支付成功！！！成交金额为：" << due_payment << " ￥" << endl;
				cout << "交易时间为：";
				this->time_format2(this->get_time());
				break;
			case 'p':case 'P':
				cout << "请输入需要支付的编号 [ ";
				for (const auto& item : id_list) {
					cout << item + 1 << " ";
				}
				cout << "]" << endl;
				while (cin >> tmp_num) {
					if (tmp_num == "y" || tmp_num == "Y") break;
					auto it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					while (it == id_list.end()) {
						cout << "请输入正确的需要支付的订单编号" << endl;
						cout << "所有需要支付的订单编号：[ ";
						for (const auto& item : id_list) {
							cout << item + 1 << " ";
						}
						cout << "]" << endl;
						cin >> tmp_num;
						it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					}
					id_list_tmp.push_back(stoi(tmp_num) - 1);

				}
				for (const auto& item_tmp : id_list_tmp) {
					if (!this->m_arr1[item_tmp]->s_pay) {
						this->m_arr1[item_tmp]->s_paytime = this->vtos(this->get_time()); //未支付过的账单才需要更新付款的时间
					}
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "部分支付成功！！！成交金额为：" << due_payment_part << " ￥" << endl;
				cout << "交易时间为：";
				this->time_format2(this->get_time());
				break;
			case 'q':case 'Q':
				cout << "已取消支付！！！" << endl;
				break;
			}
			break;
		}
	}
	else {
		cout << "Error！所查询房间号不存在！" << endl;
	}
	system("pause");
}

//查询缴费记录
void usingsystem::sear_info()
{
	// 和表的数据同步
	this->in_stu();
	cout << "请输入你的房间号" << endl;
	int num;
	cin >> num;
	cout << "查看电表账单请输入1，查看水表账单请输入2" << endl;
	int choose;
	cin >> choose;
	while (choose != 1 && choose != 2) {
		cout << "Error！输入有误。查看电表账单请输入1，查看水表账单请输入2" << endl;
		cin >> choose;
	}
	int ret = is_exist(num);
	if (ret != -1 && choose == 1) {
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|                                  电表 kWh                                |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  未支付编号  |  上一次记录日期  |  本次记录日期  |  使用量  |  应付金额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		
		int unpaid_count = 0;
		string une = "20230101";
		string unl = "20230101";
		double totalusage = 0;
		double totalprice = 0;
		vector<string> datavec1;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_type == 1) {
				//une = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 1) {
				// 未支付的
				if (!this->m_arr1[i]->s_pay) {
					unpaid_count++;
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					//unl = to_string(static_cast<int>(max(ceilf(stof(this->m_arr1[i]->s_time)), stof(unl))));
					datavec1.push_back(this->m_arr1[i]->s_time);
					totalusage += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice += this->m_arr1[i]->s_price;
				}
			}
		}
		

		if (unpaid_count == 0) {
			une = "########";
			unl = "########";
		}
		else {
			une = compareDate(datavec1, "min");
			unl = compareDate(datavec1, "max");
		}
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  总订单数目  |   最早记录日期   |  最新记录日期  |  总用量  |  应付总额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << unpaid_count << setw(8) << "|" << setw(16) << this->m_arr1[0]->timeformat(une) << setw(3) << "|" << setw(15) << this->m_arr1[0]->timeformat(unl) << setw(2) << "|" << setw(8) << totalusage << setw(3) << "|" << setw(9) << totalprice << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  已支付编号  |          半年内的缴费时间         |  使用量  |  已付金额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		
		int paid_count = 0;
		string ede = "20230101";
		string edl = "20230101";
		double totalusage2 = 0;
		double totalprice2 = 0;
		string currentdate;
		string cury = to_string(this->get_time()[0]);
		string curm = to_string(this->get_time()[1]);
		if (curm.length() != 2) curm = "0" + curm;
		string curd = to_string(this->get_time()[2]);
		if (curd.length() != 2) curd = "0" + curd;
		currentdate = cury + curm + curd;
		string halfyearago = get6month_ago(currentdate);
		vector<string> datavec2;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 1) {
				//ede = this->m_arr1[i]->s_time;
				continue;
			}

			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 1) {
				// 支付的, 且时间在半年内
				if (this->m_arr1[i]->s_pay && in6mon(this->m_arr1[i]->s_paytime, halfyearago)) {
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table2();
					paid_count++;
					//edl = to_string(static_cast<int>(max(ceilf(stof(this->m_arr1[i]->s_time)), stof(edl))));
					datavec2.push_back(this->m_arr1[i]->s_paytime.substr(0,8));
					totalusage2 += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice2 += this->m_arr1[i]->s_price;
				}
			}
		}
		if (paid_count == 0) {
			ede = "########";
			edl = "########";
		}
		else{
			edl = compareDate(datavec2, "max");
			ede = compareDate(datavec2, "min");
		}

		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  总订单数目  |   最早缴费日期   |  最新缴费日期  |  总用量  |  已付总额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << paid_count << setw(8) << "|" << setw(16) << this->m_arr1[0]->timeformat(ede) << setw(3) << "|" << setw(15) << this->m_arr1[0]->timeformat(edl) << setw(2) << "|" << setw(8) << totalusage2 << setw(3) << "|" << setw(9) << totalprice2 << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
	}
	else if (ret != -1 && choose == 2) {
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|                                  水表 m^3                                |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  未支付编号  |  上一次记录日期  |  本次记录日期  |  使用量  |  应付金额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;

		int unpaid_count = 0;
		string une = "20230101";
		string unl = "20230101";
		double totalusage = 0;
		double totalprice = 0;
		vector<string> datavec1;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_type == 2) {
				//une = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 2) {
				// 未支付的
				if (!this->m_arr1[i]->s_pay) {
					unpaid_count++;
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					//unl = to_string(static_cast<int>(max(ceilf(stof(this->m_arr1[i]->s_time)),stof(unl))));
					datavec1.push_back(this->m_arr1[i]->s_time);
					totalusage += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice += this->m_arr1[i]->s_price;
				}
			}
		}

		if (unpaid_count == 0) {
			une = "########";
			unl = "########";
		}
		else {
			une = compareDate(datavec1, "min");
			unl = compareDate(datavec1, "max");
		}
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  总订单数目  |   最早记录日期   |  最新记录日期  |  使用量  |  应付总额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << unpaid_count << setw(8) << "|" << setw(16) << this->m_arr1[0]->timeformat(une) << setw(3) << "|" << setw(15) << this->m_arr1[0]->timeformat(unl) << setw(2) << "|" << setw(8) << totalusage << setw(3) << "|" << setw(9) << totalprice << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  已支付编号  |          半年内的缴费时间         |  总用量  |  已付金额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;

		int paid_count = 0;
		string ede = "20230101";
		string edl = "20230101";
		double totalusage2 = 0;
		double totalprice2 = 0;
		string currentdate;
		string cury = to_string(this->get_time()[0]);
		string curm = to_string(this->get_time()[1]);
		if (curm.length() != 2) curm = "0" + curm;
		string curd = to_string(this->get_time()[2]);
		if (curd.length() != 2) curd = "0" + curd;
		currentdate = cury + curm + curd;
		string halfyearago = get6month_ago(currentdate);
		vector<string> datavec2;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 2) {
				//ede = this->m_arr1[i]->s_time;
				continue;
			}

			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 2) {
				// 支付的, 且时间在半年内
				if (this->m_arr1[i]->s_pay && in6mon(this->m_arr1[i]->s_paytime, halfyearago)) {
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table2();
					paid_count++;
					//edl = to_string(static_cast<int>(max(ceilf(stof(this->m_arr1[i]->s_time)), stof(edl))));
					datavec2.push_back(this->m_arr1[i]->s_paytime.substr(0, 8));
					totalusage2 += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice2 += this->m_arr1[i]->s_price;
				}
			}
		}
		if (paid_count == 0) {
			ede = "########";
			edl = "########";
		}
		else {
			edl = compareDate(datavec2, "max");
			ede = compareDate(datavec2, "min");
		}
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  总订单数目  |   最早缴费日期   |  最新缴费日期  |  总用量  |  已付总额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << paid_count << setw(8) << "|" << setw(16) << this->m_arr1[0]->timeformat(ede) << setw(3) << "|" << setw(15) << this->m_arr1[0]->timeformat(edl) << setw(2) << "|" << setw(8) << totalusage2 << setw(3) << "|" << setw(9) << totalprice2 << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
	}
	else {
		cout << "Error！所查询房间号不存在！" << endl;
	}

	system("pause");
}

//查询未缴费名单
void usingsystem::not_pay() {
	// 和表的数据同步
	this->in_stu();
	personsystem s;
	cout << "未缴费名单：" << endl;
	//对名单进行排序
	map<int, double> roommap;
	for (int i = 0; i < this->m_num; i++) {
		//未缴费的房间
		if (!this->m_arr1[i]->s_pay) {
			auto itr = roommap.find(this->m_arr1[i]->s_roomnum);  // 统计总需要付多少钱
			if (itr != roommap.end()) {
				roommap[this->m_arr1[i]->s_roomnum] += this->m_arr1[i]->s_price;
			}
			else {
				roommap[this->m_arr1[i]->s_roomnum] = this->m_arr1[i]->s_price;
			}
		}
	}
	for (auto itr = roommap.begin(); itr != roommap.end(); ++itr) {
		cout << "房间号：" << left<< setw(8) << itr->first << "   应缴金额：" << itr->second << endl;
		for (int j = 0; j < s.m_num; j++) {
			if (s.m_arr[j]->m_roomNumber == itr->first) {
				cout << right << setw(6) << "->：" << s.m_arr[j]->m_name << endl;
			}
		}
	}

	
	system("pause");
}


void usingsystem::exitsystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(6);
}
void usingsystem::menu1() {
	cout << "****1，添加用水电信息**" << endl;
	cout << "****2，查询费用********" << endl;
	cout << "****3，查询缴费记录****" << endl;
	cout << "****4，展示未缴费名单**" << endl;
	cout << "****5, 展示所有信息****" << endl;
	cout << "****6，返回主菜单******" << endl;
	cout << endl;
}