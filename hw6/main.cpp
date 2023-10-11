#include "my_string.h"
#include <iostream>

using namespace std;

int main(void) {
  MyString new_string("hello");
  cout << "Initial string:" << endl;
  new_string.print();

  cout << "Printing elements with overloaded []:\n";
  for (int i = 0; i < new_string.get_length(); i++) {
    cout << i << ": " << new_string[i] << endl;
  }

  try {
    cout << new_string[-1] << endl;
  } catch (const std::out_of_range) {
    cout << "Invalid index error caught!" << endl;
  }

  return 0;
}