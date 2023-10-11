/*
 * Реализуйте класс Дробь.
 * Необходимо хранить числитель и знаменатель в качестве переменных-членов.
 * Реализуйте функции-члены для ввода данных в переменные-члены,
 * для выполнения арифметических операций (сложение, вычитание,
 * умножение, деление, и т.д.).
 */

#include "fraction.h"
#include <iostream>

using namespace std;

int main(void) {
    cout << "Initial:\n";
    Fraction f1(1, 2); // 1/2
    Fraction f2(3, 4); // 3/4

    cout << "f1 = ";
    f1.print();
    cout << "f2 = ";
    f2.print();

    Fraction result;

    cout << "\nTests:\n";

    result = f1 + f2;
    cout << "f1 + f2 = ";
    result.print();

    result = f1 - f2;
    cout << "f1 - f2 = ";
    result.print();

    result = f1 * f2;
    cout << "f1 * f2 = ";
    result.print();

    result = f1 / f2;
    cout << "f1 / f2 = ";
    result.print();

    cout << "Division by zero check:\n";
    try {
        Fraction f3(1, 0);
    } catch (const std::exception &e) {
        cout << "Caught exception for f3: " << e.what() << endl;
    }

    return 0;
}