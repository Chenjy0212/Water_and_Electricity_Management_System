#pragma once
#include<iostream>
#include<string>
using namespace std;
#include "Person.h"
#include "CostStandard.h"

class student :public person {
public:
	student(string name, int id, int roomNumber, int UID);
	virtual void show_info();
	virtual string get_name();
};

class stucoststd : public coststandard {
public:
	stucoststd(double usage, int type);

	virtual double cal_price();
};