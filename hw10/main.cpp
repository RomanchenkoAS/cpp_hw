#include <iostream>
#include <vector>

using namespace std;

class CharStack {
private:
    vector<char> array;
public:
    CharStack() : array() {};

    size_t get_size() const {
        return array.size();
    }

    void push(char c) {
        array.push_back(c);
    }

    void pop() {
        array.pop_back();
    }

    bool is_empty() const {
        if (get_size() == 0) return true; else return false;
    }

    char get_top() const {
        return array.back();
    }
};

bool is_parenthesis(const char c) {
    if (c == '{' || c == '(' || c == '[' || c == '}' || c == ')' || c == ']') return true; else return false;
}

bool is_opening(const char c) {
    if (c == '{' || c == '(' || c == '[') return true; else return false;
}

bool is_closing(const char c) {
    if (c == '}' || c == ')' || c == ']') return true; else return false;
}

bool match(char c1, char c2) {
    if (c1 == '{' && c2 == '}') return true;
    if (c1 == '[' && c2 == ']') return true;
    if (c1 == '(' && c2 == ')') return true;
    return false;
}

bool is_valid(const string &input) {
    CharStack stack;

    for (char c: input) {
        if (is_parenthesis(c)) {

            if (is_closing(c) && stack.is_empty()) return false;
            if (is_closing(c)) {
                char top = stack.get_top();
                if (match(top, c)) stack.pop();
                else return false;
            };
            if (is_opening(c)) stack.push(c);

        }
    }
    if (!stack.is_empty()) return false; else return true;
};

int main() {

    cout << "Input string: ";
    string s1;
    getline(cin, s1);
    if (is_valid(s1)) cout << "String is valid;" << endl;
    else cout << "String is not valid;" << endl;

    return 0;
}