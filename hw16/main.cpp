#include <iostream>

template<class T>
class smart_ptr {
private:
    T *pointer;
public:
    smart_ptr(T *object) : pointer(object) {};

    ~smart_ptr() {
        std::cout << "Value inside object has been deleted." << std::endl;
        delete pointer;
    };

//    You cannot copy or assign (copy) this object
    smart_ptr(const smart_ptr &) = delete;

    smart_ptr &operator=(const smart_ptr &) = delete;

    T &operator*() {
        return *pointer;
    }
};

template<class T>
class smart_shared_ptr {
private:
    T *pointer;
    int counter = 0;
public:
    smart_shared_ptr(T *object) : pointer(object), counter(1) {};

    ~smart_shared_ptr() {
        std::cout << "Shared ptr destructor has been called." << std::endl;
        if (--counter == 0) {
            std::cout << "Value inside object has been deleted." << std::endl;
            delete pointer;
        }
    };

//    You can copy and assign this object!
    smart_shared_ptr(const smart_shared_ptr &other) : pointer(other.pointer), counter(other.counter + 1) {
        return *this;
    };

    smart_shared_ptr &operator=(const smart_shared_ptr &other) {
        if (this != &other) {
            pointer = other.pointer;
            counter = ++other.counter;
        }
        return *this;
    };

    T &operator*() {
        return *pointer;
    }
};

int main() {
    {
        smart_ptr<int> p1(new int);
        *p1 = 5;
        std::cout << "Inside local namespace:" << std::endl;
        std::cout << "Ptr 1 = " << *p1 << std::endl;
    }
    std::cout << "This is outside local namespace." << std::endl;
    return 0;
}