
#include <iostream>
#include <vector>
#include "Calendar.h"
using namespace std;


int main() {

	/*
	//Test current day
	Dayx day;
	day.puzzle1();
	day.puzzle2();
	return;
	*/
	vector<BaseDay*> calendar{ new Day1(), new Day2() };
	
	for (auto& elem : calendar)	{
		cout << "Day " << elem->getDay() << " puzzle 1: " << elem->puzzle1() << "\n";
		cout << "Day " << elem->getDay() << " puzzle 2: " << elem->puzzle2() << "\n";
		delete(elem);
	}
}