#pragma once
#include<iostream>
#include<string>
using namespace std;

class person
{
public:
	string m_name;
	int m_id;
	int m_roomNumber;
	int m_UID;

	virtual void show_info() = 0;
	virtual string get_name() = 0;
};