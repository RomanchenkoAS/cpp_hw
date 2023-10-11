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
#include <iostream>

// TODO rewrite this
// TODO Add copy constructor: Flat(const Flat& other)

class Flat {
  private:
    Person *tenants;
    int tenants_count;
    int tenants_limit;
    int rooms;

  public:
    Flat(Person *tenants, int tenants_count, int tenants_limit, int rooms)
        : tenants(tenants), tenants_count(tenants_count),
          tenants_limit(tenants_limit), rooms(rooms) {}
    Flat(int tenants_limit, int rooms)
        : Flat(nullptr, 0, tenants_limit, rooms) {}
    // Flat(Flat other) {}
    Flat() : tenants(nullptr), tenants_count(0), tenants_limit(0), rooms(0) {}
    Flat(const Flat &other)
        : tenants(new Person[other.tenants_count]),
          tenants_count(other.tenants_count),
          tenants_limit(other.tenants_limit), rooms(other.rooms) {
        for (int i = 0; i < tenants_count; i++) {
            tenants[i] = other.tenants[i];
        }
    }
    ~Flat() {
        std::cout << "trying to delete tenants in " << this << std::endl;
        delete[] this->tenants;
        this->tenants = nullptr;
        std::cout << "successfully deleted tenants in " << this << std::endl;
    }
    Flat &operator=(const Flat &other) {
        if (this == &other) {
            return *this;
        }

        delete[] tenants;
        tenants = nullptr;

        tenants_count = other.tenants_count;
        tenants_limit = other.tenants_limit;
        rooms = other.rooms;

        tenants = new Person[tenants_count];
        for (int i = 0; i < tenants_count; i++) {
            tenants[i] = other.tenants[i];
        }

        return *this;
    }
    void set_tenants(Person *new_tenants, int count) {
        delete[] tenants;
        tenants = new_tenants;
        tenants_count = count;
    }
    Person *get_tenants() const { return tenants; }

    void set_tenants_count(int count) { tenants_count = count; }
    int get_tenants_count() const { return tenants_count; }

    void set_tenants_limit(int limit) { tenants_limit = limit; }
    int get_tenants_limit() const { return tenants_limit; }

    void set_rooms(int new_rooms) { rooms = new_rooms; }
    int get_rooms() const { return rooms; }

    void add_tenant(const Person &new_tenant) {
        if (tenants_count >= tenants_limit) {
            std::cout << "Tenants limit reached." << std::endl;
            return;
        }

        Person *new_tenants = new Person[tenants_count + 1];
        for (int i = 0; i < tenants_count; i++) {
            new_tenants[i] = tenants[i];
        }
        new_tenants[tenants_count] = new_tenant;
        delete[] tenants;
        tenants = new_tenants;
        tenants_count++;
    }

    void evict_tenant(int index) {
        if (index >= 0 && index < tenants_count) {
            for (int i = index; i < tenants_count - 1; i++) {
                tenants[i] = tenants[i + 1];
            }
            tenants_count--;
        } else {
            std::cout << "Invalid tenant index." << std::endl;
        }
    }

    void evict_all_tenants() {
        delete[] tenants;
        tenants = nullptr;
        tenants_count = 0;
    }

    void print_flat_info() {
        std::cout << "Flat info: \n";
        std::cout << "Rooms: " << rooms << "\n";
        std::cout << "Tenant Limit: " << tenants_limit << "\n";
        std::cout << "Current Tenants: " << tenants_count << "\n";
    }

    void print_all_tenants() {
        std::cout << "Listing all tenants:\n";
        for (int i = 0; i < tenants_count; i++) {
            tenants[i].print();
        }
    }
};

class Building {
  private:
    Flat *flats;
    int flat_count;

  public:
    Building(Flat *init_flats, int init_flat_count)
        : flats(init_flats), flat_count(init_flat_count) {}

    Building(int init_flat_count) : Building(nullptr, init_flat_count) {}

    Building() : flats(nullptr), flat_count(0) {}
    Building(const Building &other) : flat_count(other.flat_count) {
        flats = new Flat[flat_count];
        for (int i = 0; i < flat_count; i++) {
            flats[i] = Flat(other.flats[i]);
        }
    }
    ~Building() {
        std::cout << "building destructor" << std::endl;
        if (flats != nullptr) {
            delete[] flats;
            flats = nullptr;
        }
    }
    Building &operator=(const Building &other) {
        if (this == &other)
            return *this;

        delete[] flats;
        flats = nullptr;

        flat_count = other.flat_count;

        flats = new Flat[flat_count];
        for (int i = 0; i < flat_count; i++) {
            flats[i] = Flat(other.flats[i]);
        }

        return *this;
    }

    void set_flats(Flat *new_flats, int count) {
        delete[] flats;
        flats = new_flats;
        flat_count = count;
    }
    Flat *get_flats() const { return flats; }

    void set_flat_count(int count) { flat_count = count; }
    int get_flat_count() const { return flat_count; }

    void add_flat(const Flat &new_flat) {
        Flat *new_flats = new Flat[flat_count + 1];

        for (int i = 0; i < flat_count; ++i) {
            new_flats[i] = Flat(flats[i].get_tenants(), flats[i].get_tenants_count(), flats[i].get_tenants_limit(), flats[i].get_rooms());
        }

        new_flats[flat_count] = Flat(new_flat.get_tenants(), new_flat.get_tenants_count(),
             new_flat.get_tenants_limit(), new_flat.get_rooms());

        delete[] flats;

        flats = new_flats;
        flat_count++;
    }
    void delete_flat(int index) {
        if (index >= 0 && index < flat_count) {
            Flat *new_flats = new Flat[flat_count - 1];
            for (int i = 0, j = 0; i < flat_count; i++) {
                if (i == index)
                    continue;
                new_flats[j++] = Flat(flats[i]);
            }
            delete[] flats;
            flats = new_flats;
            flat_count--;
        } else {
            std::cout << "Invalid flat index." << std::endl;
        }
    }
    void print_building_info() {
        int total_tenants = 0;
        int total_rooms = 0;
        int total_vacancies = 0;

        std::cout << "Building info: \n";
        std::cout << "Total flats: " << flat_count << "\n";

        for (int i = 0; i < flat_count; i++) {
            total_tenants += flats[i].get_tenants_count();
            total_rooms += flats[i].get_rooms();
            total_vacancies +=
                (flats[i].get_tenants_limit() - flats[i].get_tenants_count());
        }

        std::cout << "Total tenants: " << total_tenants << "\n";
        std::cout << "Total rooms: " << total_rooms << "\n";
        std::cout << "Total vacant: " << total_vacancies << "\n";
    }

    void print_all_flats_info() {
        std::cout << "Listing all flats:\n";
        for (int i = 0; i < flat_count; i++) {
            flats[i].print_flat_info();
        }
    }
};

int main(void) {
    Person valeriy("Valera", "123-4567", "987-6543",
                   "Junior software developer");
    Person dmitry("Dimonchik", "789-1234", "456-7890", "Programming teacher");
    Person sergey("Seryoga", "555-7777", "888-5555",
                  "Start-up project manager");
    Person oleg("Oleg", "789-123224", "456-7890", "Programming student");

    Flat flat1(3, 2);
    Flat flat2(2, 1);
    Flat flat3(20, 11);
    // Flat flat3; // Default constructor

    flat1.add_tenant(valeriy);
    flat1.add_tenant(dmitry);
    flat2.add_tenant(sergey);
    flat3.add_tenant(oleg);

    Flat initial_flats[] = {flat1, flat2};
    Building building(initial_flats, 2);

    building.print_building_info();
    building.print_all_flats_info();

    // std::cout << "\nEvicting a tenant from the first flat.\n";
    // flat1.evict_tenant(0);

    building.add_flat(flat3);
    std::cout << "ok" << std::endl;

    std::cout << "\nUpdated Building Information:\n";
    building.print_building_info();
    building.print_all_flats_info();

    return 0;
}