#include"usingelectricity.h"
#include <iomanip>

usingelectricity::usingelectricity(int id, int roomnum, string ltime, string time, double ldegree, double degree, double price, int type, bool pay) {
	this->s_id = id;
	this->s_roomnum = roomnum;
	this->s_ltime = ltime;
	this->s_time = time;
	this->s_ldegree = ldegree;
	this->s_degree = degree;
	this->s_price = price;
	this->s_type = type;
	this->s_pay = pay;
}
//void usingelectricity::show_info00() {
//	
//}
//string usingelectricity::get_type() {
//	
//}