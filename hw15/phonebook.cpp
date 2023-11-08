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

void Firm::create_field(char *&field, const char *input_line) {
    int length = strlen(input_line);
    field = new char[length + 1];
    strcpy(field, input_line);
}

Firm::Firm()
    : title(nullptr), owner_name(nullptr), number(nullptr),
      info(nullptr) {
    create_field(title, "");
    create_field(owner_name, "");
    create_field(number, "");
    create_field(info, "");
}
Firm::Firm(const char *name, const char *number_work,
           const char *number_mobile, const char *info) {
    create_field(this->title, name);
    create_field(this->owner_name, number_work);
    create_field(this->number, number_mobile);
    create_field(this->info, info);
}
Firm::Firm(Firm const &firm) {
    create_field(title, firm.title);
    create_field(owner_name, firm.owner_name);
    create_field(number, firm.number);
    create_field(info, firm.info);
}

// Destructor
Firm::~Firm() {
    // std::cout << "Firm destruct " << name << std::endl;
    delete[] title;
    delete[] owner_name;
    delete[] number;
    delete[] info;
}

// Methods
Firm &Firm::operator=(const Firm &other) {
    // Copy assignment
    if (this == &other)
        return *this;

    delete[] title;
    delete[] owner_name;
    delete[] number;
    delete[] info;

    create_field(title, other.title);
    create_field(owner_name, other.owner_name);
    create_field(number, other.number);
    create_field(info, other.info);

    return *this;
}
void Firm::set_name(const char *input) {
    delete[] title;
    create_field(title, input);
}
void Firm::set_number_work(const char *input) {
    delete[] owner_name;
    create_field(owner_name, input);
}
void Firm::set_number(const char *input) {
    delete[] number;
    create_field(number, input);
}
void Firm::set_info(const char *input) {
    delete[] info;
    create_field(info, input);
}

void Firm::print() {
    std::cout << title << "\n";
    std::cout << "Owner name: \t" << owner_name << "\n";
    std::cout << "Mobile phone: \t" << number << "\n";
    if (strlen(info) > 0) {
        std::cout << "Info: \t\t" << info << "\n\n";
    }
}
void Firm::print_summary() {
    std::cout << title << "; " << owner_name << "; " << number << "; "
              << info << "; \n";
}
std::string Firm::get_summary() const {
    std::string summary = std::string(title) + "; " + owner_name + "; " +
                          number + "; " + info + ";";
    return summary;
}

Phonebook::Phonebook() {
    content = new Firm[0];
    length = 0;
}
Phonebook::Phonebook(std::initializer_list<Firm> init_list) {
    // Create phonebook from a list of firms
    length = init_list.size();
    content = new Firm[length];
    int i = 0;
    for (const auto &firm : init_list) {
        content[i++] = firm;
    }
}
Phonebook::~Phonebook() {
    // std::cout << "Phonebook destruct " << std::endl;
    delete[] content;
}

void Phonebook::add(Firm const &new_firm) {
    Firm *new_content = new Firm[length + 1];

    for (int i = 0; i < length; i++) {
        new_content[i] = content[i];
    }
    new_content[length] = new_firm;
    delete[] content;
    content = new_content;
    length++;
}
void Phonebook::add(const char *input_line) {
    // Create a firm from a character string
    std::istringstream stream((std::string(input_line)));
    std::string name, number_work, number_mobile, info;

    std::getline(stream, name, ';');
    std::getline(stream, number_work, ';');
    std::getline(stream, number_mobile, ';');
    std::getline(stream, info, ';');

    Firm new_firm;
    new_firm.set_name(name.c_str());
    new_firm.set_number_work(number_work.c_str());
    new_firm.set_number(number_mobile.c_str());
    new_firm.set_info(info.c_str());

    this->add(new_firm);
}
int Phonebook::find_firm(const char *name) {
    for (int i = 0; i < length; i++) {
        if (std::strcmp(name, content[i].get_name()) == 0) {
            return i;
        }
    }
    return -1;
}
int Phonebook::delete_firm(const char *name) {
    int position = find_firm(name);
    if (position != -1) {
        Firm *new_content = new Firm[length - 1];
        Firm *ptr_from = content;

        for (Firm *ptr_to = new_content; ptr_to < new_content + length - 1;
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
Firm *Phonebook::get_firm(int index) const {
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