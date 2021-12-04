#include <iostream>
#include <fstream>
#include <array>
#include <regex>
using namespace std;

#include "Day4.h"

Day4::Day4() {
    day = 4;
    filename = "input/Day4.txt";
}

int Day4::puzzle1() {
    vector<int> drawNumbers;
    vector<Board> boards;
    FillData(drawNumbers, boards);

    for (auto drawNumber : drawNumbers) {
        for (Board& b : boards) {
            b.mark(drawNumber);
            if (b.bingo()) {
                return b.unmarked() * drawNumber;
            }
        }
    }

    return -1;
}

int Day4::puzzle2() {
    vector<int> drawNumbers;
    vector<Board> boards;
    vector<Board> boardsNoBingo;
    FillData(drawNumbers, boards);

    Board& boardNoBingo = boards[0];
    for (auto drawNumber : drawNumbers) {
        if (drawNumber == 94) {
            cout << 666;
        }
        for (Board& b : boards) {
            b.mark(drawNumber);
            if (b.bingo()) {
                if (boards.size() == 1) return b.unmarked() * drawNumber;
            }
            else {
                boardsNoBingo.emplace_back(b);
            }
        }
        boards = std::move(boardsNoBingo);
    }

    return -1;

}

void Day4::FillData(vector<int>& drawNumbers, vector<Board>& boards)
{
    ifstream ifs(filename, ios::binary);
    string drawNumbersString;
    ifs >> drawNumbersString;
    drawNumbers = std::move(numbersToVector(drawNumbersString));
    int numberBoard{};
    int numberIdx{};
    Board currentBoard;
    while (ifs >> numberBoard) {
        currentBoard.add(numberIdx, numberBoard);
        if (numberIdx == 24) { //create new board
            boards.push_back(currentBoard);
        }
        numberIdx = (numberIdx + 1) % 25;
    }
}

vector<int> Day4::numbersToVector(string str) {
    vector<int> retVector;
    std::regex regexz(",");
    vector<string> list(sregex_token_iterator(str.begin(), str.end(), regexz, -1), sregex_token_iterator());
    std::for_each(list.begin(), list.end(), [&](string s) {retVector.push_back(stoi(s));});
    return retVector;
}

void Board::mark(int number) {
    for (auto& val : arrayValues) {
        if (val == number && val == 0) val = INT_MIN;
        if (val == number) val *= -1;
    }    
}

int Board::unmarked() {
    int ret = 0;
    for (auto& val : arrayValues) {
        if (val > 0) ret += val;
    }
    return ret;
}

bool Board::bingo()
{
    
    for (int x = 0; x < 5; x++) {
        int marked = 0;
        for (int y = 0; y < 5; y++) {            
            int pos = x * 5 + y;
            if (arrayValues[pos] < 0) marked++;
            if (marked == 5) return true;
        }
    }

    for (int x = 0; x < 5; x++) {
        int marked = 0;
        for (int y = 0; y < 5; y++) {
            int pos = x + 5 * y;
            if (arrayValues[pos] < 0) marked++;
            if (marked == 5) return true;
        }
    }

    return false;
}

void Board::add(int pos, int number) {
    arrayValues[pos] = number;
}
