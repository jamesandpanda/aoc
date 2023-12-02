#include <iostream>

int main(void) {
    const std::string tokens[20] = {
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "zero", "one", "two",
        "three", "four", "five", "six", "seven", "eight", "nine"
    };

    std::string line;
    int firstDigit;
    int secondDigit;
    int sum = 0;

    while (std::getline(std::cin, line)) {
        size_t earliestPos = INT32_MAX;
        size_t largestPos = 0;

        for (int i = 0; i < 20; i++) {
            if (line.find(tokens[i]) == std::string::npos) continue;
            int temp;

            if (0 <= i && i <= 9) {
                temp = i;
            } else {
                temp = i - 10;
            }

            size_t firstPos = line.find(tokens[i]);
            size_t lastPos = line.rfind(tokens[i]);

            if (firstPos <= earliestPos) {
                earliestPos = firstPos;
                firstDigit = temp;
            }
            if (lastPos >= largestPos) {
                largestPos = lastPos;
                secondDigit = temp;
            }
        }

        sum += firstDigit * 10 + secondDigit;
    }

    std::cout << sum << "\n";

    return 0;
}