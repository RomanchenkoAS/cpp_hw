#include <cstring> // for strlen
#include <iostream>
using namespace std;

class MyString {
  private:
    char *line;

  public:
    MyString(const char *other_line) : line(nullptr) {
        line = set_line(other_line);
    };
    MyString() : MyString(""){};
    MyString(const MyString &other_string)
        : MyString(other_string.get_line()){};
    MyString(MyString &&other_string) : line(other_string.line) {
        other_string.line = nullptr;
        cout << "Move constructor worked" << endl;
    }
    ~MyString() { delete[] line; }
    char *get_line() const { return line; }
    char *set_line(const char *other_line) {
        if (line != nullptr)
            delete[] line;
        int length = strlen(other_line);
        char *result_line = new char[length + 1];
        for (int i = 0; i < length; i++) {
            result_line[i] = other_line[i];
        }
        result_line[length] = '\0';
        return result_line;
    }
    int get_length() const { return strlen(line); }
    void print() { cout << line << endl; }
};

int main(void) {
    // Parametrised constructor
    MyString new_string("hello");
    new_string.print();

    // Copy constructor
    MyString other_string(new_string);
    other_string.print();

    // Move constructor
    MyString moved_string(std::move(other_string));
    moved_string.print();
    return 0;
}