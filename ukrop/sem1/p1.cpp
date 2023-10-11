#include <iostream>

using namespace std;

#define delimiter "\n-------------\n"
class point {
  private:
    // Переменные класса тока тут
    float x;
    float y;

  public:
    float get_x() const { return x; }
    float get_y() const { return y; }
    void set_x(float x) {
        this->x = x;
    } // this - указатель на объект для которого вызывается метод
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
        cout << "Constructor\t\t" << this << endl;
    }

    // Copy onstructor
    point(const point &p) {
        this->x = p.get_x();
        this->y = p.get_y();
        cout << "Copy constructor\t" << this << endl;
    }
    // Operators
    point &operator=(const point &p) {
        this->x = p.x;
        this->y = p.y;
        cout << "Copy assignment\t\t" << this << endl;
        return *this;
    }
    // Destructor
    ~point() { cout << "Destructor\t" << this << endl; }
    //  Methods:
    void print() const { cout << "x=" << x << "\ty=" << y << endl; }

  protected:
    // Доступ только этого класса и дочерних
};

// #define STRUCT_POINT
// #define constructor_check
// # define assignment_check

int main(void) {

    cout << "ok" << endl;

#ifdef constructor_check
    // Default constructor
    point A;
    A.set_x(2);
    A.set_y(5);
    A.print();

    // Single argument constructor
    point B = 5;
    B.print();

    // Parameterd constructor (constructor)
    point C(2, 3);
    C.print();

    // Copy constructor
    point D(C);
    D.print();

    point E;
    E = D;
    E.print();
#endif

#ifdef assignment_check
    // int a, b, c;
    // a = b = c = 0;
    // cout << a << " " << b << " " << c << endl;

    point H, I, J;
    cout << delimiter << endl;
    H = I = J = point(2, 3);
    cout << delimiter << endl;
    H.print();
    I.print();
    J.print();
#endif
    int a = 2;
    int b = 3;
    int c = a + b;
    cout << c << endl;

    point A(2, 3);
    point B(4, 5);
    // point C = A + B;

    bool a1 = false, a2 = true;
    bool a3 = a1 - a2;
    cout << a3;
    return 0;
}

/*? Mandatroy methods
- Constructor - create an object
    - May be overloaded
    - Options
        - w/ params
        - w/ no params
        - default constructor (no params or with params but every param has
default variable | well be added automatically if not defined and fill fields
with rubbish)
        - copy constructor - copy object
        - move constructor
- Desctructor - clean up from memory
Only one instance of this func
- Assignment


1. Перегрузить можно только существующие операторы
2. Не все существующие операторы можно перегрузить
    Не перегружаются:
    ?: - тернарный
    :: - оператор разрешения видимости
    . - оператор прямого доступа
    .* - pointer to member selection
    # - preprocessor directive
    ## preprocessor concatenation
3. Перегруженные операторы сохраняют приоритет
4. Переопределить поведение оператора над встроенными типами невозможно

*/