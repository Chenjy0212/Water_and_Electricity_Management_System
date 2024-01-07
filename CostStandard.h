#pragma once
#include<iostream>
#include<string>
using namespace std;

class coststandard
{
public:
	double c_usage;  // 使用总量
	int c_type;   // 使用类型

	virtual double cal_price() = 0;
};