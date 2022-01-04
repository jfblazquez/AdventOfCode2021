
#include <iostream>
#include <vector>
#include <limits>
#include "Calendar.h"
using namespace std;


int main() {

	
	//Test current day
	const clock_t begin_time = clock();

	/*Day2x day;
	cout << "Day: " << day.getDay() << " puzzle1: " << day.puzzle1() << "\n";
	cout << "Day: " << day.getDay() << " puzzle2: " << day.puzzle2() << "\n";	
	std::cout << endl << "Elapsed: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;*/
	return 0;
	
	vector<BaseDay*> calendar{ 
		new Day1(),
		new Day2(),
		new Day3(),
		new Day4(),
		new Day5(),
		new Day6(),
		new Day7(),
		new Day8(),
		new Day9(),
		new Day10(),
		new Day11(),
		new Day12(),
		new Day13(),
		new Day14(),
//		new Day15(),
		new Day16(),
		new Day17(),
		new Day18(),
		new Day19(),
		new Day20(),
		new Day21(),
		new Day22()/*,
		new Day23(),
		new Day24(),
		new Day25()*/ };
	
	for (auto& elem : calendar)	{
		int p1 = elem->puzzle1();
		if (std::numeric_limits<int>::max() != p1) {
			cout << "Day " << elem->getDay() << " puzzle 1: " << p1 << "\n";
		}

		int p2 = elem->puzzle2();
		if (std::numeric_limits<int>::max() != p2) {
			cout << "Day " << elem->getDay() << " puzzle 2: " << p2 << "\n";
		}
		delete(elem);
	}
}