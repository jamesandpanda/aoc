#include <iostream>

int main(void) {
    std::string line;
    int firstDigit = -1;
    int secondDigit = -1;
    int sum = 0;

    while (std::getline(std::cin, line)) {
        bool found = false;
        for (char c : line) {
            if ('0' <= c && c <= '9') {
                if (!found) {
                    found = true;
                    firstDigit = secondDigit = c - '0';
                } else {
                    secondDigit = c - '0';
                }
            }
        }

        sum += firstDigit * 10 + secondDigit;
    }

    std::cout << sum << "\n";

    return 0;
}