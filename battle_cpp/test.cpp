#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>

int parse_int(const std::string &s) {
    int res = 0;
    for (int i = 0; i < (int) s.length(); i++) {
        int c = (int) s[i] - (int) '0';
        if (c >= 0 && c < 9) {res += (int) c * pow(10, s.length() - i - 1);}
        else {throw std::invalid_argument("Error parsing integer");}
    }

    return res;
}

int main() {
    std::unordered_map<std::string, std::string> map;
    map["0"] = "hello";
    std::string* s = &map.at("0");
    s->append(" world");
    std::cout << map.at("0") << " "  << *s << std::endl;
    map.erase("0");
    std::cout << map.contains("0") << std::endl;

    return 0;
}