#include <iostream>
#include <vector>

using namespace std;

class CharStack {
private:
    vector<char> array;
public:
    CharStack() : array() {};

    CharStack(vector<char> new_vector) : array(new_vector) {};

    size_t get_size() {
        return array.size();
    }

    void push(char c) {
        array.push_back(c);
    }

    char pop() {
        char top_element = array.front();
        array.pop_back();
        return top_element;
    }

    bool is_empty() {
        if (get_size() == 0) return true; else return false;
    }

    char get_top() const {
        return array.front();
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

bool is_valid(const string& input) {
    CharStack stack;

    for (char c: input) {
        if (is_parenthesis(c)) {

//            Cant close parenthesis before adding something
            if (is_closing(c) || stack.is_empty()) return false;
            if (is_closing(c)) {
                char top = stack.
            };
            if (is_opening(c)) stack.push(c);

        }
    }
    return false;
}

int main() {

    cout << "Input string ";
    string s1;
    getline(cin, s1);
    if (is_valid(s1)) cout << "String is valid;" << endl;
    else cout << "String is not valid;" << endl;

    return 0;
}