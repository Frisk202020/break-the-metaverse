#include <iostream>
#include <array>
#include <cmath>
#include <vector>

std::vector<std::string> split(std::string s, std::string splitter){
    std::vector<std::string> ans = {};
    size_t pos;
    while ((pos = s.find(splitter)) != std::string::npos){
        ans.push_back(s.substr(0, pos));
        s = s.substr(pos + splitter.length());
    }
    ans.push_back(s);
    ans.shrink_to_fit();
    
    return ans;
}

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
    return ((int) (ratio * value));
}

int parse_int(const std::string &s) {
    int res = 0;
    for (int i = 0; i < (int) s.length(); i++) {
        int c = (int) s[i] - (int) '0';
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

// Private function (not declared in the header)
const char* color_library(const std::string &input) {
    if (input == "red") { return "\033[31m"; }
    if (input == "green") { return "\033[32m"; }
    if (input == "yellow") { return "\033[33m"; }
    if (input == "blue") { return "\033[34m"; }
    if (input == "purple") { return "\033[35m"; }
    if (input == "cyan") { return "\033[36m"; }
    return "\033[0m";
}

const char* get_color(const std::string &input) {
    return color_library(input);
}