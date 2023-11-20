#include <iostream>

using namespace std;
int main() {

    auto isnum = [](char c) { return (bool)isdigit(c); };
    cout << isnum('1') << endl;
    cout << isnum('a') << endl;

    return 0;
}