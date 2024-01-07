#include "PersonSystem.h"
#include "UsingSystem.h"
#include <iostream>
#include <cctype>
using namespace std;

void menu() {
	cout << "*********欢迎使用缴费系统**********" << endl;
	cout << endl;
	cout << "  请根据需求输入数字使用对应功能   " << endl;
	cout << "       1  用户信息管理系统         " << endl;
	cout << "       2  缴水电费管理系统         " << endl;
	cout << "       3      退出系统             " << endl;
	cout << endl;
	cout << "***********************************" << endl;
}

//判读是否为数字
int isNumber(const std::string& input) {
	int number;
	// 检查是否为空
	if (input.empty()) {
		number = 0;
		
	}

	// 检查每个字符是否为数字
	for (char c : input) {
		if (!std::isdigit(c)) {
			 number = 0;
			 return number;
		}
	}

	// 转换为整数
	number = std::stoi(input);

	return number;
}

int main() {
	string input;
	while (true) {
		system("cls");
		menu();
		cin >> input;
		int num = isNumber(input);
		switch(num){
		case 1:
		{
			personsystem s;
			int num;
			while (true) {
				system("cls");
				s.menu2();
				cout << "请输入你要访问的步骤" << endl;
				cin >> num;
				switch (num) {
				case 1://添加信息
					s.add_info();
					break;
				case 2://删除信息
					s.del_info();
					break;
				case 3://修改信息
					s.mod_info();
					break;
				case 4://显示信息
					s.show_stu();
					break;
				case 5://返回系统
					//s.exitsystem();
					return main();
					//break;
				default:
					system("cls");
					break;
				}
			}
		}
		case 2:
		{
		usingsystem a;
		int num;
		while (true) {
			system("cls");
		 	a.menu1();
		 	cout << "请输入你要访问的步骤" << endl;
		 	cin >> num;
		 	switch (num) {
		 	case 1://添加水电表信息
		 		a.add_info();
		 		break;
		 	case 2://查询费用, 确认是否缴费
		 		a.sear_price();
		 		break;
		 	case 3://查询缴费记录
		 		a.sear_info();
		 		break;
		 	case 4://查询未缴费名单
		 		a.not_pay();
		 		break;
			case 5://显示所有信息
				a.show_stu();
				break;
		 	case 6://返回系统
		 		//a.exitsystem();
				return main();
		 		//break;
		 	default:
		 		system("cls");
		 		break;
		 	}
		}
		}
		case 3:
		{
			cout << "欢迎下次使用" << endl;
			system("pause");
			exit(3);
		}
		}
	}
}