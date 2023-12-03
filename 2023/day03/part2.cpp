#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstddef>

using namespace std;

#define MAX_LEN 140
#define INPUT_FILE_NAME "input.txt"

typedef struct Gear {
    int id;
    vector<int> nums;
} Gear;

typedef struct Coordinate {
    int i;
    int j;
} Coordinate;

bool readFile(vector<string> &lines);
int countDigits(vector<string> &lines, int i, int j);
Coordinate isAdjToGear(vector<string> &lines, int i, int j);
bool inBounds(int i, int j);
bool isGear(char c);

int main(void) {
    int sum = 0;
    vector<string> lines;
    if (!readFile(lines)) {
        return EXIT_FAILURE;
    }

    int numGears = 0;
    Gear gears[MAX_LEN][MAX_LEN];
    for (int i = 0; i < MAX_LEN; i++) {
        for (int j = 0; j < MAX_LEN; j++) {
            gears[i][j].id = (lines[i][j] == '*') ? numGears++ : -1;
        }
    }

    for (int i = 0; i < MAX_LEN; i++) {
        for (int j = 0; j < MAX_LEN; j++) {
            if (!('0' <= lines[i][j] && lines[i][j] <= '9')) continue;

            int currNum = 0;
            int dest = j + countDigits(lines, i, j) - 1;
            Coordinate ret = {-1, -1};

            while (j <= dest) {
                if (isAdjToGear(lines, i, j).i != -1) {
                    ret = isAdjToGear(lines, i, j);
                }
                currNum = currNum * 10 + (lines[i][j] - '0');
                j++;
            }

            if (ret.i != -1) {
                j--;
                gears[ret.i][ret.j].nums.push_back(currNum);
            }
        }
    }

    for (int i = 0; i < MAX_LEN; i++) {
        for (int j = 0; j < MAX_LEN; j++) {
            if (gears[i][j].nums.size() == 2) {
                sum += gears[i][j].nums[0] * gears[i][j].nums[1];
            }
        }
    }

    cout << sum << endl;

    return 0;
}

// Reads file from input files into a vector
bool readFile(vector<string> &lines) {
    ifstream file(INPUT_FILE_NAME);
    if (!file) {
        cerr << "Cannot open file" << INPUT_FILE_NAME << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return true;
}

int countDigits(vector<string> &lines, int i, int j) {
    int numDigits = 0;
    while (inBounds(i, j) && '0' <= lines[i][j] && lines[i][j] <= '9') {
        numDigits++;
        j++;
    }

    return numDigits;
}

Coordinate isAdjToGear(vector<string> &lines, int i, int j) {
    Coordinate ret = (Coordinate) {-1, -1};

    if (inBounds(i - 1, j - 1) && isGear(lines[i - 1][j - 1])) {
        ret = {i - 1, j - 1};
    } else if (inBounds(i - 1, j) && isGear(lines[i - 1][j])) {
        ret = {i - 1, j};
    } else if (inBounds(i - 1, j + 1) && isGear(lines[i - 1][j + 1])) {
        ret = {i - 1, j + 1};
    } else if (inBounds(i, j - 1) && isGear(lines[i][j - 1])) {
        ret = {i, j - 1};
    } else if (inBounds(i, j + 1) && isGear(lines[i][j + 1])) {
        ret = {i, j + 1};
    } else if (inBounds(i + 1, j - 1) && isGear(lines[i + 1][j - 1])) {
        ret = {i + 1, j - 1};
    } else if (inBounds(i + 1, j) && isGear(lines[i + 1][j])) {
        ret = {i + 1, j};
    } else if (inBounds(i + 1, j + 1) && isGear(lines[i + 1][j + 1])) {
        ret = {i + 1, j + 1};
    }

    return ret;
}

bool inBounds(int i, int j) {
    return i >= 0 && i < MAX_LEN && j >= 0 && j < MAX_LEN;
}

bool isGear(char c) {
    return c == '*';
}
