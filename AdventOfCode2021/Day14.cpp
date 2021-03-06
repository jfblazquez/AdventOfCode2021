#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <stack>
using namespace std;

#include "Day14.h"

Day14::Day14() {
    day = 14;
    filename = "input/Day14.txt";    
}

int Day14::puzzle1() {
    fillData();
    
    for (int step = 0; step < 10; step++) {
        iPolymer = polymerize();
    }
    
    for (auto c : iPolymer) {
        elemsV[c]++;
    }
    return (int)result();    
}

//read hint: a pair, create two new pairs (and remove the old one)
//Count: Read first letter of each pair and add the las letter from te original one
int Day14::puzzle2() {
    fillData();

    const clock_t begin_time = clock();

    auto endLoop = iPolymer.size() - 1;
    for (auto i = 0; i < endLoop; i++) {
        string s = iPolymer.substr(i, 2);
        pairs[s]++;
    }

    for (int step = 0; step < 40; step++) {
        map<string, long long> newStepPairs;
        for (auto& c : pairs) {
            auto result = iRules[c.first];
            auto count = c.second;
            auto newPair1 = result.substr(0, 2);
            auto newPair2 = result.substr(1, 2);
            newStepPairs[newPair1] += count;
            newStepPairs[newPair2] += count;
        }
        pairs = newStepPairs;        
    }


    for (auto& c : pairs) {
        elemsV[c.first[0]]+=c.second;
        elemsDebug[c.first[0]]+=c.second;
    }
    elemsV[iPolymer[iPolymer.size() - 1]]++;
    elemsDebug[iPolymer[iPolymer.size() - 1]]++;


    //std::cout << endl << "Elapsed(p2): " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
    cout << "Day 14 puzzle 2: " << result() << endl;
    return numeric_limits<int>::max();
}

//slow solution
/*int Day14::puzzle2() {
    fillData();

    const clock_t begin_time = clock();

    for_each(iPolymer.begin(), iPolymer.end(),
        [&](auto& c) {elemsV[c]++;});

    auto endLoop = iPolymer.size() - 1;
    for (auto i = 0; i < endLoop; i++) {
        string s = iPolymer.substr(i, 2);
        polymerizeComplex(s, 10);
    }
    std::cout << endl << "Elapsed(p2): " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
    cout << "Day 14 puzzle 2: " << result() << endl;
    return numeric_limits<int>::max();
}*/


long long Day14::result()
{
    auto itmax = max_element(elemsV.begin(), elemsV.end());
    for (auto& z : elemsV) {
        if (z == 0) z = numeric_limits<long long>::max();
    }
    
    auto itmin = min_element(elemsV.begin(), elemsV.end());
    return *itmax - *itmin;
}

string Day14::polymerize()
{
    string outputPolymer;
    auto endLoop = iPolymer.size() - 1;
    for (auto i = 0; i < endLoop; i++) {
        string s = iPolymer.substr(i, 2);
        outputPolymer += (iRules[s]);
        if (i != iPolymer.size() - 2) {
            outputPolymer.pop_back();
        }        
    }
    return outputPolymer;
}

//Recursion
/*void Day14::polymerizeComplex(string input, int steps)
{    
    if (steps == 0) return;
    string output = iRules[input];
    elemsV[output[1]]++;
    polymerizeComplex(output.substr(0, 2), steps - 1);
    polymerizeComplex(output.substr(1, 2), steps - 1);
}*/

//Stack
void Day14::polymerizeComplex(string input, int steps)
{
    stack<char[3]> ss;
    char s[3] = "as";
    stack<string> in;
    stack<int> st;
    in.push(input);
    st.push(steps);

    while (in.size()) {

        string top = in.top();
        int step = st.top();
        in.pop();
        st.pop();
        string output = iRules[top];
        elemsV[output[1]]++;
        if (step > 1) {
            in.push(output.substr(0, 2));
            in.push(output.substr(1, 2));
            st.push(step - 1);
            st.push(step - 1);
        }
    }
}

void Day14::fillData()
{
    ifstream ifs(filename, ios::binary);

    string strstream;
    getline(ifs, iPolymer); //Init
    getline(ifs, strstream); //empty line
    iRules.clear();
    elemsV.clear();
    elemsV.insert(elemsV.begin(), numeric_limits<unsigned char>::max(), 0);
    while (getline(ifs, strstream)) {
        string input = strstream.substr(0, 2);
        string output;
        output += strstream[0];
        output += strstream[6];
        output += strstream[1];
        iRules[input] = output;
    }
}
