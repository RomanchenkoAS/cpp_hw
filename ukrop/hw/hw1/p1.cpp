#include <cmath>
#include <iostream>

// TODO
// 1. Написать метод distance(), который возвращает расстояние до указанной
// точки;
// 2. Написать функцию distance(), которая возвращает расстояние между двумя
// точками;

using namespace std;

class point {
  private:
    float x;
    float y;

  public:
    float get_x() const { return x; }
    float get_y() const { return y; }
    void set_x(float x) { this->x = x; }
    void set_y(float y) { this->y = y; }

    // Constructor
    point() {
        x = y = 0;
        cout << "Default constructor\t" << this << endl;
    }
    point(float x) {
        this->x = x;
        this->y = 0;
        cout << "1 Point constructor\t" << this << endl;
    }
    point(float x, float y) {
        this->x = x;
        this->y = y;
        // cout << "Constructor\t\t" << this << endl;
    }

    // Copy constructor
    point(const point &p) {
        this->x = p.get_x();
        this->y = p.get_y();
        // cout << "Copy constructor\t" << this << endl;
    }
    // Operators
    point &operator=(const point &p) {
        this->x = p.x;
        this->y = p.y;
        // cout << "Copy assignment\t\t" << this << endl;
        return *this;
    }
    ~point() { cout << "Destructor\t" << this << endl; }

    // Methods
    void print() const { cout << "x=" << x << "\ty=" << y << endl; }
    float distance(const point &target_point) {
        return sqrt(pow(target_point.x - x, 2) + pow(target_point.y - y, 2));
    }
};

float distance(const point &point_1, const point &point_2) {
    return sqrt(pow(point_1.get_x() - point_2.get_x(), 2) +
                pow(point_1.get_y() - point_2.get_y(), 2));
}

int main(void) {

    point point_a(1, 1);
    point point_b(3, 3);

    cout << "Distance A-B (method): " << point_a.distance(point_b) << endl;
    cout << "Distance A-B (function): " << distance(point_a, point_b) << endl;
}