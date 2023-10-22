#include <iostream>
#include <vector>
#include <random>
#include <cstdlib> // for srand

using namespace std;

template<class TypeName>
class MatrixClass {
private:
    vector<vector<TypeName>> matrix;

    void erase() {
//        'Deallocate' memory by creating an empty vector and swapping them
        vector<vector<TypeName>> temp;
        matrix.swap(temp);
    }

    void size_check(const MatrixClass<TypeName> &other) const {
//        Make sure that operands have same dimensions
        if (matrix.size() != other.matrix.size() || matrix.front().size() != other.matrix.front().size()) {
            throw runtime_error("Matrix dimensions mismatch!");
        }
    }


public:
    MatrixClass() : MatrixClass({{}}) {};

    explicit MatrixClass(vector<vector<TypeName>> new_vector) : matrix(std::move(new_vector)) {};

//    Parametrized constructor to create an empty matrix with given dimensions
    explicit MatrixClass(int dimension) : matrix(vector<vector<TypeName>>(dimension, vector<TypeName>(dimension))) {};

//    Element-wise operators + - / *
    MatrixClass<TypeName> operator+(const MatrixClass<TypeName> &other) const {
        size_check(other);

        MatrixClass<TypeName> result(matrix.size());
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    MatrixClass<TypeName> operator-(const MatrixClass<TypeName> &other) const {
        size_check(other);

        MatrixClass<TypeName> result(matrix.size());
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
            }
        }
        return result;
    }

    MatrixClass<TypeName> operator*(const MatrixClass<TypeName> &other) const {
        size_check(other);

        MatrixClass<TypeName> result(matrix.size());
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                result.matrix[i][j] = matrix[i][j] * other.matrix[i][j];
            }
        }
        return result;
    }

    MatrixClass<TypeName> operator/(const MatrixClass<TypeName> &other) const {
        size_check(other);

        MatrixClass<TypeName> result(matrix.size());
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                if (other.matrix[i][j] == 0) {
                    throw runtime_error("Division by zero!");
                }
                result.matrix[i][j] = matrix[i][j] / other.matrix[i][j];
            }
        }
        return result;
    }

    void print() const {
        for (const auto &row: matrix) {
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
                    cout << "Input matrix element (" << i << ";" << j << ") : ";
                    cin >> value;
                    new_row.push_back(value);
                }
                matrix.push_back(new_row);
            }
        }
    }

    void randomize() {
        srand(time(nullptr));
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix.front().size(); j++) {
                matrix[i][j] = rand();
            }
        }
    }
};

int main() {

    MatrixClass<int> m({{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}});
    cout << "Initial matrix:" << endl;

    m.print();

//    cout << "Testing user input:" << endl;
//    m.input();
//    m.print();

    cout << "Testing randomization:" << endl;
    m.randomize();
    m.print();

    cout << "Testing float vector:" << endl;
    MatrixClass<float> f(5);
    cout << "Initial matrix:" << endl;
    f.print();
    cout << "Testing randomization:" << endl;
    f.randomize();
    f.print();

    cout << "Testing operators:" << endl;
    MatrixClass<int> m1({{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}});
    MatrixClass<int> m2({{9, 8, 7},
                        {6, 5, 4},
                        {3, 2, 1}});
    cout << "m1 + m2:" << endl;
    MatrixClass m_addition = m1 + m2;
    m_addition.print();
    cout << "m1 - m2:" << endl;
    MatrixClass m_substraction = m1 - m2;
    m_substraction.print();
    cout << "m1 * m2:" << endl;
    MatrixClass m_multiplication = m1 * m2;
    m_multiplication.print();
    cout << "m1 / m2:" << endl;
    MatrixClass m_division = m1 / m2;
    m_division.print();

    return 0;
}