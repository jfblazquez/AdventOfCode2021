#pragma once
#include <iostream>
using namespace std;
class BaseDay {
public:

	virtual int puzzle1() = 0;
	virtual int puzzle2() = 0;
	virtual ~BaseDay() = default;

	template<class input>
	void showResult(const char* func, int result) {
		cout << typeid(input).name() << "::" << func << " : " << result << endl;
	}

	int getDay() {
		return day;
	}

protected:
	int day = 0;
	string filename;
};

