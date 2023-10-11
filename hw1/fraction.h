#pragma once

class Fraction {
  private:
    int numerator, denominator;

  public:
    Fraction(int numerator, int denominator);
    Fraction();
    Fraction(const Fraction &f);
    Fraction &operator=(const Fraction &f);
    Fraction operator+(const Fraction &f);
    Fraction operator-(const Fraction &f);
    Fraction operator*(const Fraction &f);
    Fraction operator/(const Fraction &f);

    int get_numerator() const;
    int get_denominator() const;
    void set_numerator(int value);
    void set_denominator(int value);
    void full_print();
    void print();
    double evaluate();
    Fraction simplify();
};

int find_gcd(int a, int b);