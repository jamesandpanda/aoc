#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <algorithm>

using namespace std;

#define NUM_CARDS 207
#define CARD_NUM_START 5
#define WINNING_START 10
#define ELF_NUMS_START 42
#define MAX_LINE_LEN 116

int parseCardNumber(string line);
vector<int> parseWinningNumbers(string line);
vector<int> parseElfNumbers(string line);

int main(void) {
    string line;
    int numCards = 0;

    // init
    int cardAmounts[NUM_CARDS];
    for (int i = 0; i < NUM_CARDS; ++i) {
        cardAmounts[i] = 1;
    }

    while (getline(cin, line)) {
        int cardNum = parseCardNumber(line) - 1;
        vector<int> winning = parseWinningNumbers(line);
        vector<int> nums = parseElfNumbers(line);
        int numWinning = 0;

        for (int num : nums) {
            if (find(winning.begin(), winning.end(), num) != winning.end()) {
                ++numWinning;
            }
        }

        for (int i = 1; i <= numWinning; ++i) {
            cardAmounts[cardNum + i] += cardAmounts[cardNum];
        }

        numCards += cardAmounts[cardNum];
    }

    std::cout << numCards << endl;
    return 0;
}

int parseCardNumber(string line) {
    int ret = 0;
    for (int i = CARD_NUM_START; line[i] != ':'; ++i) {
        if ('0' <= line[i] && line[i] <= '9') {
            ret = ret * 10 + (line[i] - '0');
        }
    }

    return ret;
}

vector<int> parseWinningNumbers(string line) {
    vector<int> ret;
    int currNum = -1;
    for (int i = WINNING_START; line[i] != '|'; ++i) {
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
    for (int i = ELF_NUMS_START; i < MAX_LINE_LEN + 1; ++i) {
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