#pragma once
#include<iostream>
#include<string>
using namespace std;
#include"System.h"

class usingelectricity :public system1 {
public:
	usingelectricity(int id, int roomnum, string ltime, string time, double ldegree, double degree, double price, int type, bool pay, string paytime);
	/*virtual void show_info00();
	virtual string get_type();*/
};