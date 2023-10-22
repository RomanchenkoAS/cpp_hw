#include <iostream>
#include <string>
#include <utility> //for move

using namespace std;
#define SPACE ' '

class Text {
private:
    string body;
public:
    explicit Text(string initial) : body(std::move(initial)) {};

    Text() : Text("") {};

    void shorten() {
        string result = "";
        int index = 0;
//        Take all spaces until first symbol
        while (body[index] == SPACE) {
            result.push_back(body[index++]);
        }
        bool seen_space = false;
//        Skip spaces that follow another space
        for (int i = index; i < body.size(); i++) {
            if (seen_space && body[i] == SPACE) continue;
            else {
                result.push_back(body[i]);
                seen_space = (body[i] == SPACE);
            }
        }
//        Remove spaces to the right of last symbol
        result.erase(result.find_last_not_of(' ') + 1);
        body = std::move(result);
    }

    void print() const {
        cout << body << endl;
    }

};

int main() {

//    Simple test
//    Text t1("Hello    world   !    ");
//    t1.print();
//    t1.shorten();
//    t1.print();

//    User input test
    cout << "Input a string: ";
    string s1;
    getline(cin, s1);
    Text t2(s1);
    t2.print();
    t2.shorten();
    t2.print();

    return 0;
}