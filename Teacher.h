#pragma once
#include<iostream>
#include<string>
using namespace std;
#include"Person.h"
#include "CostStandard.h"

class teacher :public person {
public:
	teacher(string name, int id, int roomNumber, int UID);
	virtual void show_info();
	virtual string get_name();
};

class teccoststd : public coststandard {
public:
	teccoststd(double usage, int type);

	virtual double cal_price();
};