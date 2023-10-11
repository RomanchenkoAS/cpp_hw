/*
 * Создайте программу, имитирующую многоквартирный дом. Необходимо иметь классы
 * “Человек”, “Квартира”, “Дом”. Класс “Квартира” содержит динамический массив
 * объектов класса “Человек”. Класс “Дом” содержит массив объектов класса
 * “Квартира”. Каждый из классов содержит переменные-члены и функции-члены,
 * которые необходимы для предметной области класса. Обращаем ваше внимание, что
 * память под строковые значения выделяется динамически. Например, для ФИО в
 * классе “Человек”. Не забывайте обеспечить классы различными конструкторами
 * (конструктор копирования обязателен), деструкторами. В main протестировать
 * работу полученного набора классов.
 */

#include "person.h"
#include <cstring> // for strcmp
#include <iostream>

class Flat {
  private:
    Person *tenants;
    int tenants_count;
    int rooms;

  public:
    Flat(Person *tenants, int tenants_count, int rooms)
        : tenants(tenants), tenants_count(tenants_count), rooms(rooms){};
    Flat() : tenants(nullptr), tenants_count(0), rooms(1){};
    ~Flat() {
        delete[] tenants;
        tenants = nullptr;
    };
    Flat(const Flat &other)
        : tenants_count(other.tenants_count), rooms(other.rooms) {
        tenants = new Person[tenants_count];
        for (int i = 0; i < tenants_count; i++) {
            tenants[i] = other.tenants[i];
        }
    }
    Flat &operator=(const Flat &other) {
        if (this != &other) {
            delete[] tenants;
            tenants_count = other.tenants_count;
            rooms = other.rooms;

            tenants = new Person[tenants_count];
            for (int i = 0; i < tenants_count; i++) {
                tenants[i] = other.tenants[i];
            }
        }
        return *this;
    }
    void add_tenant(Person &new_tenant) {
        Person *new_tenants = new Person[tenants_count + 1];
        for (int i = 0; i < tenants_count; i++) {
            new_tenants[i] = tenants[i];
        }
        new_tenants[tenants_count] = new_tenant;
        if (tenants != nullptr) {
            delete[] tenants;
        }
        tenants = new_tenants;
        tenants_count++;
    }
    void delete_tenant(const char *name) {
        int index = -1;
        for (int i = 0; i < tenants_count; i++) {
            if (strcmp(tenants[i].get_name(), name) == 0) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            // std::cout << "Deleting tenant " << name << std::endl;
            Person *new_tenants = new Person[tenants_count - 1];
            int j = 0;
            for (int i = 0; i < tenants_count; i++) {
                if (i != index) {
                    new_tenants[j] = tenants[i];
                    j++;
                }
            }
            delete[] tenants;
            tenants = new_tenants;
            tenants_count--;
        } else {
            std::cout << "Tenant " << name << " not found." << std::endl;
        }
    }
    void delete_tenant(int index) {
        if (index < 0 || index >= tenants_count) {
            std::cout << "Invalid index." << std::endl;
            return;
        }

        // std::cout << "Deleting tenant with index " << index << std::endl;
        Person *new_tenants = new Person[tenants_count - 1];
        int j = 0;
        for (int i = 0; i < tenants_count; i++) {
            if (i != index) {
                new_tenants[j] = tenants[i];
                j++;
            }
        }
        delete[] tenants;
        tenants = new_tenants;
        tenants_count--;
    }
    void print_summary() const {
        std::cout << "This flat has " << rooms << " rooms and " << tenants_count
                  << " tenants: " << std::endl;
        for (int i = 0; i < tenants_count; i++) {
            tenants[i].print_summary();
        }
    }
    void print_tenants() const {
        for (int i = 0; i < tenants_count; i++) {
            tenants[i].print();
        }
    }
    int get_rooms() const { return tenants_count; }
    int get_tenants_count() const { return tenants_count; }
    void set_rooms(int count) { tenants_count = count; }
    void set_tenants_count(int count) { tenants_count = count; }
};

class Building {
  private:
    Flat *flats;
    int flat_count;

  public:
    Building() : flats(nullptr), flat_count(0) {}
    Building(Flat *new_flats, int new_count)
        : flats(new_flats), flat_count(new_count) {}
    ~Building() {
        delete[] flats;
        flats = nullptr;
    }
    Building(const Building &other) : flat_count(other.flat_count) {
        flats = new Flat[flat_count];
        for (int i = 0; i < flat_count; i++) {
            flats[i] = other.flats[i];
        }
    }
    Building &operator=(const Building &other) {
        if (this != &other) {
            delete[] flats;

            flat_count = other.flat_count;
            flats = new Flat[flat_count];
            for (int i = 0; i < flat_count; i++) {
                flats[i] = other.flats[i];
            }
        }
        return *this;
    }
    void add_flat(Flat &new_flat) {
        Flat *new_flats = new Flat[flat_count + 1];
        for (int i = 0; i < flat_count; i++) {
            new_flats[i] = flats[i];
        }
        new_flats[flat_count] = new_flat;
        if (flats != nullptr) {
            delete[] flats;
        }
        flats = new_flats;
        flat_count++;
    }
    void delete_flat(int index) {
        if (index < 0 || index >= flat_count) {
            std::cout << "Invalid index." << std::endl;
            return;
        }
        Flat *new_flats = new Flat[flat_count - 1];
        int j = 0;
        for (int i = 0; i < flat_count; i++) {
            if (i != index) {
                new_flats[j] = flats[i];
                j++;
            }
        }
        delete[] flats;
        flats = new_flats;
        flat_count--;
    }
    void print_building_info() const {
        std::cout << "The building has " << flat_count << " flats."
                  << std::endl;
    }
    void print_all_flats_info() const {
        for (int i = 0; i < flat_count; i++) {
            std::cout << "Flat " << i + 1 << ":" << std::endl;
            flats[i].print_summary();
            std::cout << std::endl;
        }
    }
    int get_flat_count() const { return flat_count; }
    void set_flat_count(int count) { flat_count = count; }
};

// This is for the full check including testing Flat class
#define fullcheck

int main(void) {
    Person valeriy("Valera", "123-4567", "987-6543",
                   "Junior software developer");
    Person dmitry("Dimonchik", "789-1234", "456-7890", "Programming teacher");
    Person sergey("Seryoga", "555-7777", "888-5555",
                  "Start-up project manager");

#ifdef fullcheck
    // Testing adding tenants
    std::cout << "Creation of flat:\n";
    Flat f;
    f.add_tenant(valeriy);
    std::cout << "Added 1 tenant:\n";
    f.print_tenants();
    f.add_tenant(dmitry);
    std::cout << "Added 2 tenants:\n";
    f.print_tenants();
    f.add_tenant(sergey);
    std::cout << "Added 3 tenants:\n";
    f.print_tenants();
    std::cout << "Short info:\n";
    f.print_summary();

    // Testing deletion tenants
    std::cout << "\n\nDeleting tenants:\n";
    f.delete_tenant(0);
    std::cout << "Deleted 1 tenant:\n";
    f.print_tenants();
    f.delete_tenant("Dimonchik");
    std::cout << "Deleted 2 tenants:\n";
    f.print_tenants();
    std::cout << "Short info:\n";
    f.print_summary();
#endif

    // Testing building class
    std::cout << "\n\nCreation of building:\n";
    Building b;
    Flat flat1, flat2;
    flat1.add_tenant(valeriy);
    flat1.add_tenant(dmitry);

    b.add_flat(flat1);
    std::cout << "Added 1 flat:\n";
    b.print_all_flats_info();

    flat2.add_tenant(sergey);
    b.add_flat(flat2);

    std::cout << "Added 2 flats:\n";
    b.print_all_flats_info();
    std::cout << "Building info:\n";
    b.print_building_info();

    // Testing deletion of flats
    std::cout << "\n\nDeleting flats:\n";
    b.delete_flat(0);
    std::cout << "Deleted 1 flat:\n";
    b.print_all_flats_info();
    b.delete_flat(0);
    std::cout << "Deleted 2 flats:\n";
    b.print_all_flats_info();
    std::cout << "Building info:\n";
    b.print_building_info();

    return 0;
}