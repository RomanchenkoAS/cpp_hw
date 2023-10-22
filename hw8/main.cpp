#include <iostream>
#include <vector>

using namespace std;

template<class TypeName>
class Matrix {
private:
    vector<vector<TypeName>> matrix;

    void erase() {
//        'Deallocate' memory by creating an empty vector and swapping them
        vector<vector<TypeName>> temp;
        matrix.swap(temp);
    }

public:
    Matrix() : Matrix({{}}) {};

    Matrix(vector<vector<TypeName>> new_vector) : matrix(std::move(new_vector)) {};

    void print() const {
        for (auto row: matrix) {
            for (auto element: row) {
                cout << element << " ";
            }
            cout << endl;
        }
    }

    void input() {
        erase();
        int dimension = 0;
        cout << "Input matrix dimension: ";
        cin >> dimension;
        if (dimension < 2) {
            cout << "Incorrect value, dimensions cannot be <2." << endl;
            return;
        } else {
            TypeName value;
            for (int i = 0; i < dimension; i++) {
                vector<TypeName> new_row;
                for (int j = 0; j < dimension; j++) {
                    cout << "Input matrix element (" << i << ";" << j << ") :";
                    cin >> value;
                    new_row.push_back(value);
                }
                matrix.push_back(new_row);
            }
        }
    }

};

int main() {

    Matrix<int> m({{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9}});
    m.print();

    cout << "Testing user input:" << endl;
    m.input();
    m.print();
    return 0;
}