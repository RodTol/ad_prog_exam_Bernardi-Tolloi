//copied in class, just the last part of the main is missing

#include <array>
#include <iostream>
#include <vector>

using namespace std;

enum class month{jan=1,feb,mar,apr,may,jun,jul,sep,oct,nov,dec};

class Date{
	private:
		int _day;
		month _month;  //Can't be called month because of conflict
		int _year;
	public:
		int get_day() const{
			return _day;
		}
		month get_month() const{
			return _month;
		}
		int get_year() const{
			return _year;
		}
		void add_month_small(int quant){
			_month = static_cast<month>(static_cast<int>(_month)+quant);
			return;
		}
		void add_day_small(int quant){
			_day += quant;
			return;
		}
		void add_year(int quant){
			_year += quant;
			return;
		}
		void print(){
			cout << "Current date: " << _day << " " << int(_month) << " " << _year << " " << endl;
			return;
		}
		Date(){
			_day = 1;
			_month = month::jan;
			_year = 2000;
			cout << "Initialised Date 01/01/2000";
		}
		Date(int day,month month,int year){
			_day = day;
			_month = month;
			_year = year;
		}
		int days_in_current_month();
		int missing_days_to_month();
		void add_days(const unsigned int n);
};


int Date::days_in_current_month(){
	month this_month = get_month();
	int days_current_month;
	switch(this_month){
		case month::nov:
		case month::apr:
		case month::jun:
		case month::sep:
			days_current_month = 30;
			break;
		case month::feb:
			days_current_month = 28;
			break;
		default:
			days_current_month = 31;
			break;
	}
	return days_current_month;
}


int Date::missing_days_to_month(){
	month this_month = get_month();
	int days_left = days_in_current_month()-get_day();
	return days_left;
}

void Date::add_days(const unsigned int n){
	unsigned int days_to_add{n};
	unsigned int this_month{static_cast<unsigned int> (get_month())};
	unsigned int months_to_add{0};
	unsigned int year_to_add{0};
	while (days_to_add > static_cast<unsigned int> (missing_days_to_month())){
		months_to_add += 1;
		days_to_add -= (static_cast<unsigned int> (missing_days_to_month())+1);
		if (months_to_add > (12-this_month) and ((months_to_add + this_month - 1) % 12) == 0){
			++year_to_add;
			add_month_small(-11);
		}
		else{
			add_month_small(1);
		}
	}
	
	add_day_small(days_to_add);
	add_year(year_to_add);
	
	return;
}

bool operator==(const Date& lhs, const Date& rhs){
	return lhs.get_year() == rhs.get_year()
	&& lhs.get_month() == rhs.get_month()
	&& lhs.get_day() == rhs.get_day();
}

bool operator!=(const Date& lhs, const Date& rhs){
	return !(lhs==rhs);
}


ostream& operator<<(ostream& os, const Date& d){
	os << "Day: " << d.get_day() << "\n" << "Month: " << static_cast<int>(d.get_month()) << "\n" << "Year: " << d.get_year() << endl;
	return os;
}


int main(){
	Date mydate1(5,month::feb,2010);
	Date mydate(6,month::jan,2001);
	std::cout << mydate.Date::get_day() << "\n";
	//std::cout << mydate.Date::get_month() << "\n";
	std::cout << mydate.Date::get_year() << "\n";
	//std::cout << mydate.Date::add_day_small(5) << "\n";
	
}



