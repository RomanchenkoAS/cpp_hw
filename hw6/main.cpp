#include "my_string.h"
#include <iostream>

using namespace std;

int main(void) {
  MyString new_string("hello");
  cout << "Full string:" << endl;
  new_string.print();

  cout << "Printing elements with overloaded []:\n";

  for (int i = 0; i < new_string.get_length(); i++) {
    cout << i << ": " << new_string[i] << endl;
  }

  return 0;
}