#include <iostream>
#include <algorithm> // for sort
#include <utility> // IDE added this idk what for
#include <vector>    // for vector

using namespace std;

template<class T>
class VectorArray {
private:
    vector<T> array;

    int search(T element, int begin, int end) {
        if (begin <= end) {
            int mid = begin + (end - begin) / 2;
            if (array[mid] == element) return mid;
            if (array[mid] > element) return search(element, begin, mid - 1);
            return search(element, mid + 1, end);
        }
        return -1;
    }

public:
    explicit VectorArray(vector<T> new_array) : array(std::move(new_array)) {};

    VectorArray() : array() {};

    void print() {
        for (auto element: array) {
            cout << element << endl;
        }
    }

    void print_inline() {
        for (auto element: array) {
            cout << element << "\t";
        }
        cout << endl;
    }

    bool operator==(const VectorArray &other) {
        if (this->get_size() != other.get_size()) {
            return false;
        }
        for (int i = 0; i < array.size(); i++) {
            if (array[i] != other[i]) {
                return false;
            }
        }
        return true;
    }

    int get_size() const {
        return array.size();
    }

    T operator[](int i) const {
        return array[i];
    }

    void sort() {
        std::sort(array.begin(), array.end());
    }

    bool is_sorted() {
        for (int i = 0; i < get_size() - 1; i++) {
            if (array[i] > array[i + 1]) return false;
        }
        return true;
    }

    int binary_search(T element) {
        if (!is_sorted()) throw logic_error("Logic error: Array must be sorted before binary search.");
        return search(element, 0, get_size() - 1);
    }

    void set_element(int index, T element) {
        array[index] = element;
    }
};

int main() {

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
    cout << "Checking equality operator: " << endl;

    VectorArray arr1(vector<int>{10, 2, 3, 4, 5, 0, 1});
    VectorArray arr2(vector<int>{10, 2, 3, 4, 5, 0, 1, 1});

    bool equality1 = (arr1 == arr2);
    cout << "Equality 1 = " << equality1 << endl;

    VectorArray arr3(vector<int>{10, 2, 3, 4, 5, 0, 1});
    VectorArray arr4(vector<int>{10, 2, 3, 4, 5, 0, 1});

    bool equality2 = (arr3 == arr4);
    cout << "Equality 2 = " << equality2 << endl;

    vector<int> arr5 = {10, 2, 3, 4, 5, 0, 1};
    VectorArray object5(arr5);
    cout << "\nBinary search:\nLook for 5 in array:" << endl;
    object5.print_inline();
    cout << "\nExpect an error:" << endl;
    try {
        int result = object5.binary_search(5);
        cout << "Found 5 at position " << result << endl;

    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }
    object5.sort();
    cout << "Look for 5 in array:" << endl;
    object5.print_inline();
    cout << "\nExpect a value:" << endl;
    try {
        int result = object5.binary_search(5);
        cout << "Found 5 at position " << result << endl;

    } catch (const std::exception &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}