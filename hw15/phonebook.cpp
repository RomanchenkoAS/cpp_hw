#include "phonebook.h"
#include <cstring> // strlen
#include <fstream> // ifstream, ofstream
#include <iostream>
#include <sstream> // istringstream

int get_int(std::string message) {
    // Function displays a message and prompts user for input. If string is not
    // a valid int, it repeats.istringsststream
    int result;
    std::string input;
    while (true) {
        std::cout << message;
        std::cin >> input;

        bool is_valid = true;

        // Cycle to check if value is a valid integer
        for (int i = 0; i < input.length(); i++) {
            if ((input[i] < '0' || input[i] > '9') && (input[i] != '-')) {
                // If a character is not one of allowed ones, return false as
                // result
                is_valid = false;
            }
        }

        if (is_valid) {
            result = stoi(input);
            break;
        }
    }
    return result;
}

void testing() {
// #define test_person
// #define test_phonebook
// #define test_read_file
#ifdef test_person
    Person p;
    std::cout << "Empty person:" << std::endl;
    p.print();

    p.set_name("Albert Einstein");
    p.set_number_work("112");
    p.set_number_mobile("8-800-555-35-35");
    p.set_info("Generally recognized german physicist and mathematician");
    std::cout << delimiter << "Filled person object:" << std::endl;
    p.print();

    Person p1(p);
    std::cout << delimiter << "Copied person object:" << std::endl;
    p1.print();

    return 0;
#endif
#ifdef test_phonebook
    Person p1("Albert Einstein", "+7-705-449-4570", "+7-999-870-9797",
              "Generally recognized german physicist and mathematician");
    Person p2("Isaac Newton", "+44-703-959-2514", "+44-759-123-5678",
              "English mathematician and physicist");
    Person p3(
        "Marie Curie", "+33-655-564-901", "+33-612-345-678",
        "Polish-born physicist and chemist, first woman to win a Nobel Prize");
    Person p4("Nikola Tesla", "+1-555-443-2211", "+1-555-987-6543",
              "Serbian-American inventor, electrical engineer, and futurist");
    Person p5(
        "Ada Lovelace", "+44-777-532-3421", "+44-888-765-4321",
        "English mathematician, known for her work on the Analytical Engine");
    Person p6("Galileo Galilei", "+39-333-123-4545", "+39-333-678-9012",
              "Italian astronomer, physicist and polymath");

    // That is a stupid way to fill a phonebook
    // Phonebook book;
    // book.add(p1);
    // book.add(p2);
    // book.add(p3);
    // book.add(p4);
    // book.add(p5);
    // book.add(p6);

    // That's better
    Phonebook book({p1, p2, p3, p4, p5, p6});
    book.print();
    book.save_to_file("database.txt");
#endif
#ifdef test_read_file
    Phonebook book;
    if (book.read_from_file("database.txt") != 0) {
        std::cout << "Failed to read database!\n";
        return 1;
    }

    book.print();

#endif
    return;
}

void Person::create_field(char *&field, const char *input_line) {
    int length = strlen(input_line);
    field = new char[length + 1];
    strcpy(field, input_line);
}

Person::Person()
    : name(nullptr), number_work(nullptr), number_mobile(nullptr),
      info(nullptr) {
    create_field(name, "");
    create_field(number_work, "");
    create_field(number_mobile, "");
    create_field(info, "");
}
Person::Person(const char *name, const char *number_work,
               const char *number_mobile, const char *info) {
    create_field(this->name, name);
    create_field(this->number_work, number_work);
    create_field(this->number_mobile, number_mobile);
    create_field(this->info, info);
}
Person::Person(Person const &source_person) {
    create_field(name, source_person.name);
    create_field(number_work, source_person.number_work);
    create_field(number_mobile, source_person.number_mobile);
    create_field(info, source_person.info);
}

// Destructor
Person::~Person() {
    // std::cout << "Person destruct " << name << std::endl;
    delete[] name;
    delete[] number_work;
    delete[] number_mobile;
    delete[] info;
}

// Methods
Person &Person::operator=(const Person &other) {
    // Copy assignment
    if (this == &other)
        return *this;

    delete[] name;
    delete[] number_work;
    delete[] number_mobile;
    delete[] info;

    create_field(name, other.name);
    create_field(number_work, other.number_work);
    create_field(number_mobile, other.number_mobile);
    create_field(info, other.info);

    return *this;
}
void Person::set_name(const char *input) {
    delete[] name;
    create_field(name, input);
}
void Person::set_number_work(const char *input) {
    delete[] number_work;
    create_field(number_work, input);
}
void Person::set_number_mobile(const char *input) {
    delete[] number_mobile;
    create_field(number_mobile, input);
}
void Person::set_info(const char *input) {
    delete[] info;
    create_field(info, input);
}

void Person::print() {
    std::cout << name << "\n";
    std::cout << "Work phone: \t" << number_work << "\n";
    std::cout << "Mobile phone: \t" << number_mobile << "\n";
    if (strlen(info) > 0) {
        std::cout << "Info: \t\t" << info << "\n\n";
    }
}
void Person::print_summary() {
    std::cout << name << "; " << number_work << "; " << number_mobile << "; "
              << info << "; \n";
}
std::string Person::get_summary() const {
    std::string summary = std::string(name) + "; " + number_work + "; " +
                          number_mobile + "; " + info + ";";
    return summary;
}

Phonebook::Phonebook() {
    content = new Person[0];
    length = 0;
}
Phonebook::Phonebook(std::initializer_list<Person> init_list) {
    // Create phonebook from a list of persons
    length = init_list.size();
    content = new Person[length];
    int i = 0;
    for (const auto &person : init_list) {
        content[i++] = person;
    }
}
Phonebook::~Phonebook() {
    // std::cout << "Phonebook destruct " << std::endl;
    delete[] content;
}

void Phonebook::add(Person const &new_person) {
    Person *new_content = new Person[length + 1];

    for (int i = 0; i < length; i++) {
        new_content[i] = content[i];
    }
    new_content[length] = new_person;
    delete[] content;
    content = new_content;
    length++;
}
void Phonebook::add(const char *input_line) {
    // Create a person from a character string
    std::istringstream stream((std::string(input_line)));
    std::string name, number_work, number_mobile, info;

    std::getline(stream, name, ';');
    std::getline(stream, number_work, ';');
    std::getline(stream, number_mobile, ';');
    std::getline(stream, info, ';');

    Person new_person;
    new_person.set_name(name.c_str());
    new_person.set_number_work(number_work.c_str());
    new_person.set_number_mobile(number_mobile.c_str());
    new_person.set_info(info.c_str());

    this->add(new_person);
}
int Phonebook::find_person(const char *name) {
    for (int i = 0; i < length; i++) {
        if (std::strcmp(name, content[i].get_name()) == 0) {
            return i;
        }
    }
    return -1;
}
int Phonebook::delete_person(const char *name) {
    int position = find_person(name);
    if (position != -1) {
        Person *new_content = new Person[length - 1];
        Person *ptr_from = content;

        for (Person *ptr_to = new_content; ptr_to < new_content + length - 1;
             ptr_to++) {
            if (std::strcmp(ptr_from->get_name(), name) != 0) {
                *ptr_to = *ptr_from;
            }
            ptr_from++;
        }
        delete[] content;
        content = new_content;
        length--;
        return 0;
    } else {
        return 1;
    }
}
Person *Phonebook::get_person(int index) const {
    if (index < 0 || index >= length) {
        return nullptr;
    } else {
        return &content[index];
    }
}
void Phonebook::print(bool summary) const {
    if (summary) {
        for (int i = 0; i < length; i++) {
            content[i].get_summary();
        }
    } else {
        for (int i = 0; i < length; i++) {
            content[i].print();
        }
    }
}
int Phonebook::save_to_file(const char *filename) {
    std::ofstream output_file(filename);
    if (!output_file.is_open()) {
        std::cerr << "Error opening the output file.\n";
        return 1;
    }
    for (int i = 0; i < length; i++) {
        output_file << content[i].get_summary() << std::endl;
    }
    output_file.close();
    return 0;
}
int Phonebook::read_from_file(const char *filename, bool clear) {
    if (clear) {
        delete[] content;
        content = nullptr;
    } else {
        std::ifstream input_file;
        input_file.open(filename);

        if (!input_file.is_open()) {
            std::cerr << "Error opening the input file.\n";
            return 1;
        }

        char line[512];
        while (input_file.getline(line, 512)) {
            this->add(line);
        }
        input_file.close();
    }
    return 0;
}