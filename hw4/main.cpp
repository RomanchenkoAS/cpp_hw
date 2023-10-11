/*
 * Разработать класс Reservoir(водоем). Класс должен обязательно иметь поле
 * «название». Класс должен содержать: конструктор по умолчанию, конструктор с
 * параметрами, при необходимости реализовать деструктор и конструктор
 * копирования. Добавить методы для:
 * 1. Определения приблизительного объема (ширина*длина*максимальная глубина);
 * 2. Определения площади водной поверхности;
 * 3. Метод для проверки относятся ли водоемы к одному
 * типу (море-море; бассейн-пруд);
 * 4. Для сравнения площади водной поверхности водоемов одного типа;
 * 5. Для копирования объектов;
 * 6. Остальные методы на усмотрение разработчика (методы set и get).
 * Написать интерфейс для работы с классом. Реализовать
 * динамический массив объектов класса с возможностью
 * добавления, удаления объектов из массива. Реализовать
 * возможность записи информации об объектах массива
 * в текстовый файл, бинарный файл.
 * Используйте explicit конструктор и константные функции-члены (например, для
 * отображения данных о водоёме и т.д.).
 */

#include <fstream> // for ofstream
#include <iostream>
#include <string> // because i can't use dynamic char arrays like my grandfather did
#include <vector> // same goes here :)
using namespace std;

class Reservoir {
  private:
    string name, type;
    int width, length, avg_depth;

  public:
    // Parametrized constructor
    Reservoir(string name, string type, int width, int length, int avg_depth)
        : name(name), type(type), width(width), length(length),
          avg_depth(avg_depth){};

    // Default constructor
    Reservoir() : name(""), type(""), width(0), length(0), avg_depth(0){};

    // Getters
    string get_name() const { return name; }
    string get_type() const { return type; }
    int get_width() const { return width; }
    int get_length() const { return length; }
    int get_avg_depth() const { return avg_depth; }

    // Setters
    void set_name(const string new_name) { name = new_name; }
    void set_type(const string new_type) { type = new_type; }
    void set_width(int new_width) { width = new_width; }
    void set_length(int new_length) { length = new_length; }
    void set_avg_depth(int new_avg_depth) { avg_depth = new_avg_depth; }

    int get_area() const { return width * length; }
    int get_volume() const { return width * length * avg_depth; }
    void print_info() const {
        cout << name << " (type:" << type << ")" << endl;
        cout << " width: \t" << width << endl;
        cout << " length: \t" << length << endl;
        cout << " average depth: " << avg_depth << endl;
    }
    bool is_same_type(const Reservoir &other) const {
        return (this->type == other.type);
    }
    int area_compare(const Reservoir &other) const {
        // Returns 1 if *this* area is larger to other's
        // Returns 0 if *this* area is equal to other's
        // Returns -1 if *this* area is smaller than other's
        if (this->get_area() == other.get_area()) {
            return 0;
        } else {
            if (this->get_area() > other.get_area()) {
                return 1;
            } else {
                return -1;
            }
        }
    }
    void copy_from(const Reservoir &other) {
        this->set_name(other.get_name());
        this->set_type(other.get_type());
        this->set_width(other.get_width());
        this->set_length(other.get_length());
        this->set_avg_depth(other.get_avg_depth());
    }
};

int main(void) {
    vector<Reservoir> reservoirs;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add a reservoir\n";
        cout << "2. Delete a reservoir\n";
        cout << "3. List all reservoirs\n";
        cout << "4. Save to a text file\n";
        cout << "5. Save to a binary file\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, type;
            int width, length, avg_depth;
            cin.ignore();
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter type: ";
            getline(cin, type);
            cout << "Enter width: ";
            cin >> width;
            cout << "Enter length: ";
            cin >> length;
            cout << "Enter average depth: ";
            cin >> avg_depth;

            Reservoir new_reservoir(name, type, width, length, avg_depth);
            reservoirs.push_back(new_reservoir);

            break;
        }

        case 2: {
            int index;
            cout << "Enter index of reservoir to delete: ";
            cin >> index;
            if (index >= 0 && index < reservoirs.size()) {
                reservoirs.erase(reservoirs.begin() + index);
                cout << "Reservoir deleted.\n";
            } else {
                cout << "Invalid index.\n";
            }
            break;
        }

        case 3: {
            for (size_t i = 0; i < reservoirs.size(); i++) {
                cout << "Reservoir " << i + 1 << ":\n";
                reservoirs[i].print_info();
            }
            break;
        }

        case 4: {
            ofstream file("reservoirs.txt");
            for (const auto &r : reservoirs) {
                file << r.get_name() << " " << r.get_type() << " "
                     << r.get_width() << " ";
                file << r.get_length() << " " << r.get_avg_depth() << "\n";
            }
            file.close();
            cout << "Data saved to reservoirs.txt\n";
            break;
        }

        case 5: {
            ofstream file("reservoirs.bin", ios::binary);
            for (const auto &r : reservoirs) {
                file.write((char *)&r, sizeof(r));
            }
            file.close();
            cout << "Data saved to reservoirs.bin\n";
            break;
        }
        case 6:
            return 0;

        default:
            cout << "Invalid choice. Please choose again.\n";
        }
    }
}