#include <iostream>
#include <algorithm> // for sort
#include <vector>    // for vector

using namespace std;

template <class T>
class VectorArray
{
private:
  vector<T> array;

public:
  VectorArray(vector<T> new_array) : array(new_array){};
  VectorArray() : array(){};
  void print()
  {
    for (auto element : array)
    {
      cout << element << endl;
    }
  }
  VectorArray &operator==(const VectorArray &other)
  {
    if (array.size() != other.size())
    {
      return false;
    }
    for (int i = 0; i < array.size(); i++)
    {
      if (array[i] != other[i])
      {
        return false;
      }
    }
    return true;
  }
  int size()
  {
    return array.size();
  }
  T operator[](int i) const
  {
    return array[i];
  }
  void sort()
  {
    std::sort(array.begin(), array.end());
  }
  int binary_search(int index, T element)
  {
    VectorArray copy = // TODO we need copy constructor here
  }
  void set_element(int index, T element)
  {
    array[index] = element;
  }
};

int main(void)
{

  // Checking constructor
  cout << "henlo" << endl;
  vector<int> arr = {10, 2, 3, 4, 5, 0, 1};
  VectorArray object(arr);

  // Checking print and sort
  object.print();
  object.sort();
  cout << "\n\nsorted:" << endl;
  object.print();

  // Checking == operator
  vector<int> arr1 = {10, 2, 3, 4, 5, 0, 1};
  vector<int> arr2 = {10, 2, 3, 4, 5, 0, 1, 1};

  bool equality1 = (arr1 == arr2);
  cout << "Equality 1 = " << equality1 << endl;

  vector<int> arr3 = {10, 2, 3, 4, 5, 0, 1};
  vector<int> arr4 = {10, 2, 3, 4, 5, 0, 1};

  bool equality2 = (arr3 == arr4);
  cout << "Equality 2 = " << equality2 << endl;


  return 0;
}