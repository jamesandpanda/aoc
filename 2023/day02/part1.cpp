#include <iostream>
#include <string>
#include <cstddef>

using namespace std;

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14
#define ID_DIGIT_1_POS 5
#define ID_DIGIT_2_POS 6

int count(string line, string token);

int main(void) {
    string line;
    int sum = 0;
    while (getline(cin, line)) {
        int numRed = count(line, "red");
        int numGreen = count(line, "green");
        int numBlue = count(line, "blue");
        
        if (numRed <= MAX_RED && numGreen <= MAX_GREEN && numBlue <= MAX_BLUE) {
            int first = line[ID_DIGIT_1_POS] - '0';
            if (line[ID_DIGIT_2_POS] == ':') {
                sum += first;
                cout << first << "\n";
            } else {
                sum += first * 10 + (line[ID_DIGIT_2_POS] - '0');
                cout << first * 10 + (line[ID_DIGIT_2_POS] - '0') << "\n";
            }
        }
    }

    cout << sum << endl;
    return 0;
}

int count(string line, string token) {
    size_t found = line.find(token);
    int max = 0;

    while (found != string::npos) {
        int first = (line[found - 3] == ' ') ? 0 : line[found - 3] - '0';
        int second = line[found - 2] - '0';

        max = std::max(max, first * 10 + second);
        found = line.find(token, found + 1);
    }

    return max;
}