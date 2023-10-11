#pragma once
#include <cstring> // for strlen
#include <iostream>
#include <stdexcept> // for out_of_range instead of assert

using namespace std;

class MyString {
private:
  char *line;

public:
  MyString(const char *other_line) : line(nullptr) {
    line = set_line(other_line);
  };

  MyString() : MyString(""){};

  MyString(const MyString &other_string) : MyString(other_string.get_line()){};

  MyString(MyString &&other_string) : line(other_string.line) {
    other_string.line = nullptr;
    std::cout << "Move constructor worked" << std::endl;
  }

  ~MyString() { delete[] line; }

  char operator[](int i) {
    if (i < 0 || i >= strlen(line)) {
      throw out_of_range("Invalid index");
    }
    return line[i];
  }

  int operator()(const char character) const {
    for (int i = 0; i < strlen(line); i++) {
      if (line[i] == character) return i;
    }
    return -1;
  }

  operator int() const { return get_length(); }
  
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

  void print() { std::cout << line << std::endl; }
};