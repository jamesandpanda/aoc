#include <iostream>
#include <string>
#include <cstddef>

using namespace std;

int count(string line, string token);

int main(void) {
    string line;
    int sum = 0;
    while (getline(cin, line)) {
        int maxRed = count(line, "red");
        int maxGreen = count(line, "green");
        int maxBlue = count(line, "blue");

        sum += maxRed * maxGreen * maxBlue;
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