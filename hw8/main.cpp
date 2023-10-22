#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Matrix {
private:
    vector<vector<T>> matrix;
public:
    Matrix() : Matrix({{}}) {};

    Matrix(vector<vector<T>> new_vector) : matrix(std::move(new_vector)) {};

    void print() const {
        for (auto row: matrix) {
            for (auto element: row) {
                cout << element << " ";
            }
            cout << endl;
        }
    }
    void input() {
        int dimension = 0;
        cout << "Input matrix dimension: ";
        cin >> dimension;
        if (dimension < 2) {
            cout << "Incorrect value, dimensions cannot be <2." << endl;
            return;
        } else {
            for (int )
        }
    }
};

int main() {

    Matrix<int> m({{1,2,3},{4,5,6},{7,8,9}});
    m.print();
    return 0;
}