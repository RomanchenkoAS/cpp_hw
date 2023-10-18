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
  VectorArray &operator=(const VectorArray &other)
  {
    if (array.size() != other.size())
    {
      return false;
    }
    for (int i = 0; i < array.size(); i++)
    {
      if !(array[i] == other[i])
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
  }
  void set_element(int index, T element)
  {
    array[index] = element;
  }
};

int main(void)
{

  cout << "henlo" << endl;
  vector<int> arr = {10, 2, 3, 4, 5, 0, 1};
  VectorArray object(arr);
  object.print();
  object.sort();
  cout << "\n\nsorted:" << endl;
  object.print();
  return 0;
}