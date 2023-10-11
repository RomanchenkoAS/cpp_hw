#pragma once
#include <cstring> // strlen
#include <fstream> // ifstream, ofstream
#include <iostream>
#include <sstream> // istringstream

class Person {
  private:
    char *name, *number_work, *number_mobile, *info;

    void create_field(char *&field, const char *input_line) {
        int length = strlen(input_line);
        field = new char[length + 1];
        strcpy(field, input_line);
    }

  public:
    Person()
        : name(nullptr), number_work(nullptr), number_mobile(nullptr),
          info(nullptr) {
        create_field(name, "");
        create_field(number_work, "");
        create_field(number_mobile, "");
        create_field(info, "");
    }

    Person(const char *name, const char *number_work, const char *number_mobile,
           const char *info) {
        create_field(this->name, name);
        create_field(this->number_work, number_work);
        create_field(this->number_mobile, number_mobile);
        create_field(this->info, info);
    }

    Person(Person const &other) {
        create_field(name, other.name);
        create_field(number_work, other.number_work);
        create_field(number_mobile, other.number_mobile);
        create_field(info, other.info);
    }

    ~Person() {
        // std::cout << "trying to delete person " << this << std::endl;
        if (name != nullptr) {
            delete[] name;
            name = nullptr;
        }
        if (number_work != nullptr) {
            delete[] number_work;
            number_work = nullptr;
        }
        if (number_mobile != nullptr) {
            delete[] number_mobile;
            number_mobile = nullptr;
        }
        if (info != nullptr) {
            delete[] info;
            info = nullptr;
        }
        // std::cout << "deleted person " << this << std::endl;
    }

    Person &operator=(const Person &other) {
        if (this == &other)
            return *this;

        char *new_name, *new_number_work, *new_number_mobile, *new_info;

        create_field(new_name, other.name);
        create_field(new_number_work, other.number_work);
        create_field(new_number_mobile, other.number_mobile);
        create_field(new_info, other.info);

        delete[] name;
        delete[] number_work;
        delete[] number_mobile;
        delete[] info;

        name = nullptr;
        number_work = nullptr;
        number_mobile = nullptr;
        info = nullptr;

        name = new_name;
        number_work = new_number_work;
        number_mobile = new_number_mobile;
        info = new_info;

        return *this;
    }

    void set_name(const char *input) {
        delete[] name;
        create_field(name, input);
    }

    void set_number_work(const char *input) {
        delete[] number_work;
        create_field(number_work, input);
    }

    void set_number_mobile(const char *input) {
        delete[] number_mobile;
        create_field(number_mobile, input);
    }

    void set_info(const char *input) {
        delete[] info;
        create_field(info, input);
    }

    const char *get_name() const { return name; }
    const char *get_number_work() const { return number_work; }
    const char *get_number_mobile() const { return number_mobile; }
    const char *get_info() const { return info; }

    void print() {
        std::cout << name << "\n";
        std::cout << "Work phone: \t" << number_work << "\n";
        std::cout << "Mobile phone: \t" << number_mobile << "\n";
        if (strlen(info) > 0) {
            std::cout << "Info: \t\t" << info << "\n\n";
        }
    }

    void print_summary() {
        std::cout << name << "; " << number_work << "; " << number_mobile
                  << "; " << info << "; \n";
    }

    std::string get_summary() const {
        std::string summary = std::string(name) + "; " + number_work + "; " +
                              number_mobile + "; " + info + ";";
        return summary;
    }
};