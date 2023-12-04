#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <algorithm>

using namespace std;

#define WINNING_START 10
#define ELF_NUMS_START 42
#define MAX_LINE_LEN 116

vector<int> parseWinningNumbers(string line);
vector<int> parseElfNumbers(string line);

int main(void) {
    string line;
    int sum = 0;

    while (getline(cin, line)) {
        vector<int> winning = parseWinningNumbers(line);
        vector<int> nums = parseElfNumbers(line);
        int mult = 0;

        for (int num : nums) {
            if (find(winning.begin(), winning.end(), num) != winning.end()) {
                mult = (mult == 0) ? 1 : mult * 2;
            }
        }
        sum += mult;
    }

    cout << sum << endl;
    return 0;
}

vector<int> parseWinningNumbers(string line) {
    vector<int> ret;
    int currNum = -1;
    for (int i = WINNING_START; line[i] != '|'; i++) {
        if ('0' <= line[i] && line[i] <= '9') {
            int digit = line[i] - '0';
            currNum = (currNum == -1) ? digit : currNum * 10 + digit;
        } else if (currNum != -1) {
            ret.push_back(currNum);
            currNum = -1;
        }
    }

    return ret;
}

vector<int> parseElfNumbers(string line) {
    vector<int> ret;
    int currNum = -1;
    for (int i = ELF_NUMS_START; i < MAX_LINE_LEN + 1; i++) {
        if ('0' <= line[i] && line[i] <= '9') {
            int digit = line[i] - '0';
            currNum = (currNum == -1) ? digit : currNum * 10 + digit;
        } else if (currNum != -1) {
            ret.push_back(currNum);
            currNum = -1;
        }
    }

    return ret;
}