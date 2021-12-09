#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <array>
#include <exception>
#include <cmath>
#include <ctime>
using namespace std;

#include "Day8.h"

Day8::Day8() {
    day = 8;
    filename = "input/Day8.txt";
}

int Day8::puzzle1() {
	ifstream ifs(filename, ios::binary);
	std::regex digit_regex(" \\| | ");

	string line;

	array<int,8> count{ 0,0,0,0,0,0,0,0 };
	while (getline(ifs, line, '\n')) {
		if (*(line.end()-1) == '\r') line.erase(line.end() - 1, line.end()); //deal with win format if needed
		vector<string> v;
		auto itbegin = std::sregex_token_iterator(line.begin(), line.end(), digit_regex, -1);
		auto itend = std::sregex_token_iterator();
		std::copy(itbegin, itend, std::back_inserter(v)); // 14 per line
		for (int i = 10; i < 14; i++) {
			count[v[i].size()]++;
		}
	}

	return count[2] + count[3] + count[4] + count[7];
}

int Day8::puzzle2() {

	const clock_t begin_time = clock();

	ifstream ifs(filename, ios::binary);
	std::regex digit_regex(" \\| | ");

	string line;

	int sum = 0;
	while (getline(ifs, line, '\n')) {
		vector<string> lineValues;
		auto itbegin = std::sregex_token_iterator(line.begin(), line.end(), digit_regex, -1);
		auto itend = std::sregex_token_iterator();
		std::copy(itbegin, itend, std::back_inserter(lineValues)); // 14 per line
		sum += processLine(lineValues);
	}

	std::cout << "Elapsed: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

	return sum;
}

int Day8::processLine(vector<string>& lineValues)
{
	int ret = 0;
	for (auto& data : lineValues) { //Order is not useful
		sort(data.begin(), data.end());
	}
	vector<string> segments(lineValues.begin(), lineValues.begin() + 10);
	vector<string> counter(lineValues.begin() + 10, lineValues.begin() + 14);
	vector<int> elemToNumber = bruteForce(segments);

	for (int i = 3; i >= 0; i--) {
		auto result = find(segments.begin(), segments.end(), counter[i]);
		int pos = result - segments.begin();
		int number = elemToNumber[pos];
		ret += number * std::pow(10, 3 - i);
	}
	return ret;
}

void Day8::getSegments(vector<string>& input)
{
	//TODO: Avoid brute force
	vector<string> numbers;
	numbers.insert(numbers.begin(), 10, "");
	for (auto& segments : input) {
		if (segments.size() == 2) numbers[2] = segments;
		else if (segments.size() == 3) numbers[3] = segments;
		else if (segments.size() == 4) numbers[4] = segments;
		else if (segments.size() == 7) numbers[7] = segments;
	}
}

vector<int> Day8::bruteForce(vector<string>& inputInit)
{
	vector<string> original = { "123567","36","13457","13467","2346","12467","124567","136","1234567","123467" };

	vector<int> ret;
	vector<string> input;
	for (auto a = '1'; a <= '7'; a++) {		
		for (auto b = '1'; b <= '7'; b++) {
			for (auto c = '1'; c <= '7'; c++) {
				for (auto d = '1'; d <= '7'; d++) {
					for (auto e = '1'; e <= '7'; e++) {
						for (auto f = '1'; f <= '7'; f++) {
							for (auto g = '1'; g <= '7'; g++) {
								if (a!= b && a!= c && a != d && a != e && a != f && a != g 
									&& b != c && b != d && b != e && b != e && b!= f && b != g 
									&& c != d && c != e && c != f && c != g
									&& d != e && d != f && d != g
									&& e != f && e != g
									&& f != g) {
									input = inputInit;
									for_each(input.begin(), input.end(), [&](string& s) {replace(s.begin(), s.end(), 'a', a);});
									for_each(input.begin(), input.end(), [&](string& s) {replace(s.begin(), s.end(), 'b', b);});
									for_each(input.begin(), input.end(), [&](string& s) {replace(s.begin(), s.end(), 'c', c);});
									for_each(input.begin(), input.end(), [&](string& s) {replace(s.begin(), s.end(), 'd', d);});
									for_each(input.begin(), input.end(), [&](string& s) {replace(s.begin(), s.end(), 'e', e);});
									for_each(input.begin(), input.end(), [&](string& s) {replace(s.begin(), s.end(), 'f', f);});
									for_each(input.begin(), input.end(), [&](string& s) {replace(s.begin(), s.end(), 'g', g);});
									bool same = true;
									for (auto& segments : input) {
										sort(segments.begin(), segments.end());
										auto result = find(original.begin(), original.end(), segments);
										same = result != original.end();
										if (!same) break;
									}
									if (same == true) {
										for (auto& segments : input) {
											auto result = find(original.begin(), original.end(), segments);
											ret.push_back(result - original.begin());											
										}
										return ret;
									}

								}
							}
						}
					}
				}
			}
		}
	}

	throw exception();
	cout << "end" << endl;
}