#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstddef>

using namespace std;

#define MAX_LEN 140
#define INPUT_FILE_NAME "input.txt"

bool readFile(vector<string> &lines);
int countDigits(vector<string> &lines, int i, int j);
bool isAdjToSymbol(vector<string> &lines, int i, int j);
bool inBounds(int i, int j);
bool isSymbol(char c);

int main(void) {
    int sum = 0;
    vector<string> lines;
    if (!readFile(lines)) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < MAX_LEN; i++) {
        for (int j = 0; j < MAX_LEN; j++) {
            if (!('0' <= lines[i][j] && lines[i][j] <= '9')) continue;
            
            int currNum = 0;
            bool adj = false;
            int dest = j + countDigits(lines, i, j) - 1;
            
            while (j <= dest) {
                if (isAdjToSymbol(lines, i, j)) adj = true;
                currNum = currNum * 10 + (lines[i][j] - '0');
                j++;
            }

            if (adj) {
                j--;
                sum += currNum;
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

bool isAdjToSymbol(vector<string> &lines, int i, int j) {
    if (inBounds(i - 1, j - 1) && isSymbol(lines[i - 1][j - 1])) return true;
    if (inBounds(i - 1, j) && isSymbol(lines[i - 1][j])) return true;
    if (inBounds(i - 1, j + 1) && isSymbol(lines[i - 1][j + 1])) return true;
    if (inBounds(i, j - 1) && isSymbol(lines[i][j - 1])) return true;
    if (inBounds(i, j + 1) && isSymbol(lines[i][j + 1])) return true;
    if (inBounds(i + 1, j - 1) && isSymbol(lines[i + 1][j - 1])) return true;
    if (inBounds(i + 1, j) && isSymbol(lines[i + 1][j])) return true;
    if (inBounds(i + 1, j + 1) && isSymbol(lines[i + 1][j + 1])) return true;

    return false;
}

bool inBounds(int i, int j) {
    return i >= 0 && i < MAX_LEN && j >= 0 && j < MAX_LEN;
}

bool isSymbol(char c) {
    return !('0' <= c && c <= '9') && !(c == '.');
}
