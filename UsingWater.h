#pragma once
#include<iostream>
#include<string>
using namespace std;
#include"system.h"

class usingwater :public system1 {
public:
	usingwater(int id, int roomnum, string ltime, string time, double ldegree, double degree, double price, int type, bool pay);
	//virtual void show_info00();
	//virtual string get_type();
};