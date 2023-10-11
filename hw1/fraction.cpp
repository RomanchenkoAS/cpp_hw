#include "fraction.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int find_gcd(int a, int b) {
    // Euclidean algorithm
    if (a < b)
        swap(a, b);

    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }

    return a;
}

// Constructors
Fraction::Fraction(int numerator, int denominator) {
    if (denominator == 0) {
        throw invalid_argument("denominator cannot be zero");
    }
    this->numerator = numerator;
    this->denominator = denominator;
}
Fraction::Fraction() {
    this->numerator = 1;
    this->denominator = 1;
}
Fraction::Fraction(const Fraction &f) {
    this->numerator = f.get_numerator();
    this->denominator = f.get_denominator();
}

// Operators
Fraction &Fraction::operator=(const Fraction &f) {
    this->numerator = f.numerator;
    this->denominator = f.denominator;
    return *this;
}
Fraction Fraction::operator+(const Fraction &f) {
    Fraction result(*this);
    if (f.denominator == this->denominator) {
        result.numerator += f.numerator;
        return result.simplify();
    } else {
        int numerator, denominator;
        numerator =
            result.numerator * f.denominator + f.numerator * result.denominator;
        denominator = result.denominator * f.denominator;
        result.numerator = numerator;
        result.denominator = denominator;
        return result.simplify();
    }
}
Fraction Fraction::operator-(const Fraction &f) {
    Fraction result(*this);
    if (f.denominator == this->denominator) {
        this->numerator -= f.numerator;
        return result.simplify();

    } else {
        int numerator, denominator;
        numerator =
            result.numerator * f.denominator - f.numerator * result.denominator;
        denominator = result.denominator * f.denominator;
        result.numerator = numerator;
        result.denominator = denominator;
        return result.simplify();
    }
}
Fraction Fraction::operator*(const Fraction &f) {
    Fraction result(*this);
    result.numerator *= f.numerator;
    result.denominator *= f.denominator;
    return result.simplify();
}
Fraction Fraction::operator/(const Fraction &f) {
    Fraction result(*this);
    result.numerator *= f.denominator;
    result.denominator *= f.numerator;
    return result.simplify();
}

// Methods
int Fraction::get_numerator() const { return numerator; }
int Fraction::get_denominator() const { return denominator; }
void Fraction::set_numerator(int value) { this->numerator = value; }
void Fraction::set_denominator(int value) {
    if (value == 0) {
        throw invalid_argument("denominator cannot be zero");
    }
    this->denominator = value;
}
void Fraction::full_print() {
    cout << "numerator: " << this->numerator << endl;
    cout << "denominator: " << this->denominator << endl;
}
void Fraction::print() {
    cout << this->numerator << " / " << this->denominator << endl;
}
double Fraction::evaluate() {
    return double(this->numerator) / this->denominator;
}
Fraction Fraction::simplify() {
    int divisor = find_gcd(this->numerator, this->denominator);
    Fraction result(this->numerator / divisor, this->denominator / divisor);
    if (result.denominator < 0) {
        result.numerator *= -1;
        result.denominator *= -1;
    }
    return result;
}