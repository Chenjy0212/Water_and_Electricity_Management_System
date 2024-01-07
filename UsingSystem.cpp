#include"UsingElectricity.h"
#include"PersonSystem.h"
#include"UsingSystem.h"
#include"UsingWater.h"
#include <iostream>
#include <algorithm>
using namespace std;

int g_var1 = 0;

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
			<< this->m_arr1[i]->s_pay << endl;
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

	int num = 0;
	while (ifs >> id && ifs >> roomnum && ifs >> ltime && ifs >> time && ifs >> ldegree && ifs >> degree && ifs >> price && ifs >> type && ifs >> pay) {
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

	int index = 0;
	while (ifs >> id && ifs >> roomnum && ifs >> ltime && ifs >> time && ifs >> ldegree && ifs >> degree && ifs >> price && ifs >> type && ifs >> pay) {
		system1* system = NULL;
		if (type == 1) {
			system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay);
		}
		if (type == 2) {
			system = new usingwater(id, roomnum, ltime, time, ldegree, degree, price, 2, pay);
		}
		this->m_arr1[index] = system;
		index++;
	}
}

//显示所有信息
void usingsystem::show_stu() {
	if (this->m_file) {
		cout << "文件为空" << endl;
	}
	else {
		cout << "当前水电记录总共有 " << this->get_num() << " 条" << endl;
		for (int i = 0; i < this->m_num; i++) {
			this->m_arr1[i]->show_info00();
			cout << endl;
		}
	}
	system("pause");
	system("cls");
}
//添加信息
void usingsystem::add_info() {
	personsystem s;

	cout << "请输入你要添加的水电表数目" << endl;
	int addnum = 0;
	cin >> addnum;

	if (addnum > 0) {
		int newsize = this->m_num + addnum;//计算新空间大小
		system1** newspace1 = new system1 * [newsize];//在堆区开辟新空间
		if (this->m_arr1 != NULL) //将原空间下内容放到新空间下
		{
			for (int i = 0; i < this->m_num; i++)
			{
				newspace1[i] = this->m_arr1[i];
			}
		}
		for (int i = 0; i < addnum; i++) {
			int id;
			int roomnum;
			string time;
			string ltime = "20230101";
			double degree;
			double ldegree = 0;
			double price;
			bool pay = false;
			if(i != 0){ 
				cout << endl; 
			}
			id = ++g_var1;
			cout << "请输入第 " << i+1 << " 个房间号" << endl;
			cin >> roomnum;
			int ret = s.is_exist2(roomnum);
			while (ret == -1) {
				cout << "房间号不正确，请重新输入" << endl;
				cin >> roomnum;
				ret = s.is_exist2(roomnum);
			}
			cout << "请输入第" << i + 1 << "个的抄表时间(eg：20240101)" << endl;
			cin >> time;
			cout << "电表输入1，水表输入2" << endl;
			int num;
			cin >> num;
			while (num != 1 && num != 2) {
				cout << "Error！输入有误。电表输入1，水表输入2" << endl;
				cin >> num;
			}
			switch (num)
			{
			case 1:
				cout << "请输入第" << i + 1 << "个的当前用电表数" << endl;
				break;
			case 2:
				cout << "请输入第" << i + 1 << "个的当前水表数" << endl;
				break;
			}
			cin >> degree;

			// 自动获取上次记录时间和使用的量
			bool exite_flag = false;
			for (int i = 0; i < this->m_num; i++)
			{
				// 如果之前有记录的话
				if (this->m_arr1[i]->s_roomnum == roomnum && this->m_arr1[i]->s_type == num) {
					//根据是不同的表有不同的结果
					exite_flag = true;
					ldegree = max(m_arr1[i]->s_degree, ldegree);
					ltime = to_string(static_cast<int>(max(stof(this->m_arr1[i]->s_time), stof(ltime))));
				}
			}
			if (!exite_flag){ // 如果没有记录,那么初始化，且设定为已经支付
				ldegree = degree;
				ltime = time;
				pay = true;
			}

			system1* system = NULL;
			switch (num) {
			case 1: {
				if(s.m_arr[ret]->m_UID == 1){
					stucoststd* scs = new stucoststd(degree - ldegree, num);
					price = scs->cal_price();
					delete scs;
					system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay);
					break;
				}
				else {
					teccoststd* tcs = new teccoststd(degree - ldegree, num);
					price = tcs->cal_price();
					delete tcs;
					system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay);
					break;
				}
			}
			case 2: {
				if (s.m_arr[ret]->m_UID == 1) {
					stucoststd* scs = new stucoststd(degree - ldegree, num);
					price = scs->cal_price();
					delete scs;
					system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 2, pay);
					break;
				}
				else {
					teccoststd* tcs = new teccoststd(degree - ldegree, num);
					price = tcs->cal_price();
					delete tcs;
					system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 2, pay);
					break;
				}
			}
			}
			newspace1[this->m_num + i] = system;
		}
	
		delete[]this->m_arr1;      //释放原来的空间
		this->m_arr1 = newspace1;  //更改新空间的指向
		this->m_num = newsize;     //更改新的个数
		this->m_file = false;      //更新不为空标志
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
				if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay) continue;
				if (this->m_arr1[i]->s_roomnum == num) {
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
			cout << "全部支付请输入“a or A”；选择支付请输入“p or P”使用“y or Y”结束； 取消支付请输入“q or Q”。" << endl;
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
					this->m_arr1[item-1]->s_pay = true;
				}
				this->m_save();
				cout << "全部支付成功！！！成交金额为：" << due_payment << " ￥" << endl;
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
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "部分支付成功！！！成交金额为：" << due_payment_part << " ￥" << endl;
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
			cout << "总共 " << count << " 笔订单, 未支付共有 " << unpaid_count << " 笔未支付" << endl;
			cout << "应缴费总金额为：" << due_payment << " ￥" << endl;
			cout << "全部支付请输入“a or A”；选择支付请输入“p or P”使用“y or Y”结束； 取消支付请输入“q or Q”。" << endl;
	
			cin >> ypq;
			while (ypq != 'a' && ypq != 'A' && ypq != 'P' && ypq != 'p' && ypq != 'q' && ypq != 'Q') {
				cout << "Error！输入有误。全部支付请输入“a or A”；选择支付请输入“p or P”使用“y or Y”结束；取消支付请输入“q or Q”。" << endl;
				cin >> ypq;
			}
			switch (ypq)
			{
			case 'a':case 'A':
				for (const auto& item : id_list) {
					this->m_arr1[item - 1]->s_pay = true;
				}
				this->m_save();
				cout << "全部支付成功！！！成交金额为：" << due_payment << " ￥" << endl;
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
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "部分支付成功！！！成交金额为：" << due_payment_part << " ￥" << endl;
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
			cout << "全部支付请输入“a or A”；选择支付请输入“p or P”使用“y or Y”结束； 取消支付请输入“q or Q”。" << endl;
			cin >> ypq;
			while (ypq != 'a' && ypq != 'A' && ypq != 'P' && ypq != 'p' && ypq != 'q' && ypq != 'Q') {
				cout << "Error！输入有误。全部支付请输入“a or A”；选择支付请输入“p or P”使用“y or Y”结束；取消支付请输入“q or Q”。" << endl;
				cin >> ypq;
			}
			switch (ypq)
			{
			case 'a':case 'A':
				for (const auto& item : id_list) {
					this->m_arr1[item - 1]->s_pay = true;
				}
				this->m_save();
				cout << "全部支付成功！！！成交金额为：" << due_payment << " ￥" << endl;
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
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "部分支付成功！！！成交金额为：" << due_payment_part << " ￥" << endl;
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
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 1) {
				une = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 1) {
				// 未支付的
				if (!this->m_arr1[i]->s_pay) {
					unpaid_count++;
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					unl = to_string(static_cast<int>(max(stof(this->m_arr1[i]->s_time), stof(unl))));
					totalusage += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice += this->m_arr1[i]->s_price;
				}
			}
		}
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  总订单数目  |   最早记录日期   |  最迟记录日期  |  使用量  |  应付总额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << unpaid_count << setw(8) << "|" << setw(16) << une.substr(0, 4) + "年" + une.substr(4, 2) + "月" + une.substr(6, 2) + "日" << setw(3) << "|" << setw(15) << unl.substr(0, 4) + "年" + unl.substr(4, 2) + "月" + unl.substr(6, 2) + "日" << setw(2) << "|" << setw(8) << totalusage << setw(3) << "|" << setw(9) << totalprice << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  已支付编号  |  上一次记录日期  |  本次记录日期  |  总用量  |  已付金额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		
		int paid_count = 0;
		string ede = "20230101";
		string edl = "20230101";
		double totalusage2 = 0;
		double totalprice2 = 0;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 1) {
				ede = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 1) {
				// 支付的
				if (this->m_arr1[i]->s_pay) {
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					paid_count++;
					edl = to_string(static_cast<int>(max(stof(this->m_arr1[i]->s_time), stof(edl))));
					totalusage2 += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice2 += this->m_arr1[i]->s_price;
				}
			}
		}
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << paid_count << setw(8) << "|" << setw(16) << ede.substr(0, 4) + "年" + ede.substr(4, 2) + "月" + ede.substr(6, 2) + "日" << setw(3) << "|" << setw(15) << edl.substr(0, 4) + "年" + edl.substr(4, 2) + "月" + edl.substr(6, 2) + "日" << setw(2) << "|" << setw(8) << totalusage2 << setw(3) << "|" << setw(9) << totalprice2 << setw(4) << "|" << endl;
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
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 2) {
				une = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 2) {
				// 未支付的
				if (!this->m_arr1[i]->s_pay) {
					unpaid_count++;
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					cout << this->m_arr1[i]->s_time << endl;
					unl = to_string(static_cast<int>(max(stof(this->m_arr1[i]->s_time),stof(unl))));
					totalusage += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice += this->m_arr1[i]->s_price;
				}
			}
		}

		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  总订单数目  |   最早记录日期   |  最迟记录日期  |  使用量  |  应付总额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << unpaid_count << setw(8) << "|" << setw(16) << une.substr(0, 4) + "年" + une.substr(4, 2) + "月" + une.substr(6, 2) + "日" << setw(3) << "|" << setw(15) << unl.substr(0, 4) + "年" + unl.substr(4, 2) + "月" + unl.substr(6, 2) + "日" << setw(2) << "|" << setw(8) << totalusage << setw(3) << "|" << setw(9) << totalprice << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  已支付编号  |  上一次记录日期  |  本次记录日期  |  总用量  |  已付金额  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;

		int paid_count = 0;
		string ede = "20230101";
		string edl = "20230101";
		double totalusage2 = 0;
		double totalprice2 = 0;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 2) {
				ede = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 2) {
				// 支付的
				if (this->m_arr1[i]->s_pay) {
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					paid_count++;
					edl = to_string(static_cast<int>(max(stof(this->m_arr1[i]->s_time), stof(edl))));
					totalusage2 += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice2 += this->m_arr1[i]->s_price;
				}
			}
		}

		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << paid_count << setw(8) << "|" << setw(16) << ede.substr(0, 4) + "年" + ede.substr(4, 2) + "月" + ede.substr(6, 2) + "日" << setw(3) << "|" << setw(15) << edl.substr(0, 4) + "年" + edl.substr(4, 2) + "月" + edl.substr(6, 2) + "日" << setw(2) << "|" << setw(8) << totalusage2 << setw(3) << "|" << setw(9) << totalprice2 << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
	}
	else {
		cout << "Error！所查询房间号不存在！" << endl;
	}

	system("pause");
}

////查询未缴费名单
void usingsystem::not_pay() {}
//	personsystem s;
//	cout << "未缴费名单：" << endl;
//	for (int i = 0; i < this->m_num; i++) {
//		if (this->m_arr1[i]->s_price != 0) {
//			for (int j = 0; j < s.m_num; j++) {
//				if (s.m_arr[j]->m_roomNumber = this->m_arr1[i]->s_id) {
//					cout << s.m_arr[j]->m_name << endl;
//				}
//			}
//		}
//	}
//}


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
	cout << "****5，返回主菜单******" << endl;
	cout << endl;
}