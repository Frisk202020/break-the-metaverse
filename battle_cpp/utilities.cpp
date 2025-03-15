#include <iostream>
#include <array>
#include <cmath>

int ask_for_superguard(const std::string &name) {
    std::string prompt;
    std::cout << "Did " << name << " tried to superguard ?\n";
    std::getline(std::cin, prompt);
    if (prompt[0] == 'y') {
        std::cout << "Did he successfully superguard ?\n";
        std::getline(std::cin, prompt);
        if (prompt[0] == 'y') {return 1;}
        else {return -1;}
    }
    return 0;
}

int entropy(const int value, const int min, const int var){
    double ratio = (min + rand()%var) / 100.;
    return ((int) ratio * value);
}

int parse_int(const std::string &s) {
    int res;
    for (int i = 0; i < (int) s.length(); i++) {
        char c = s[i] - '0';
        if (c >= 0 && c < 9) {res += (int) c * pow(10, s.length() - i - 1);}
        else {throw std::invalid_argument("Error parsing integer");}
    }

    return res;
}

bool happening(const int odd){
    bool arr[100] = {};
    std::fill(arr, arr + odd, true);
    std::fill(arr + odd, arr + 100, false);

    return arr[rand()%100];
}