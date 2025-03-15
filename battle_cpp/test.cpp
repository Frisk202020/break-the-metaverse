#include <iostream>
#include <vector>

int main() {
    std::vector<int> v; v.reserve(100);
    v.push_back(5);
    std::cout << v[0] << '\n';

    return 0;
}