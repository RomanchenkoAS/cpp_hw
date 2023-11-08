#include "phonebook.h"
#include <cstring> // strlen
#include <iostream>

int main(void) {
    Phonebook phonebook;

    while (true) {
        std::string name, number_work, number_mobile, info;
        std::cout << delimiter;
        int input = get_int(
                "Choose action:\n1 - Show all \n2 - Add \n3 - Delete \n4 - Find "
                "\n5 - Save to file \n6 - Load file \n0 - Exit \n-------- Your "
                "action: ");
        switch (input) {
            case 1: {
                phonebook.print();
                break;
            }
            case 2: {
                std::cin.ignore();
                std::cout << "Name:\t\t";
                std::getline(std::cin, name);
                std::cout << "Work number:\t";
                std::getline(std::cin, number_work);
                std::cout << "Mobile number:\t";
                std::getline(std::cin, number_mobile);
                std::cout << "Info:\t\t";
                std::getline(std::cin, info);
                std::string add_line = name + "; " + number_work + "; " +
                                       number_mobile + "; " + info + "; ";
                phonebook.add(add_line.c_str());
                break;
            }
            case 3: {
                std::cin.ignore();
                std::cout << "Enter firm title to delete: ";
                std::getline(std::cin, name);
                if (phonebook.delete_firm(name.c_str()) != 0) {
                    std::cout << "Firm was not found.\n";
                };
                break;
            }
            case 4: {
                std::cin.ignore();
                std::cout << "Enter firm title to find: ";
                std::getline(std::cin, name);
                int position = phonebook.find_firm(name.c_str());
                if (position == -1) {
                    std::cout << "Person " << name << " was not found\n";
                } else {
                    Firm *found = phonebook.get_firm(position);
                    found->print();
                }
                break;
            }
            case 5: {
                std::string filename;
                std::cout << "Enter filename to save: ";
                std::cin >> filename;
                phonebook.save_to_file(filename.c_str());
                break;
            }
            case 6: {
                std::string filename;
                std::cout << "Enter filename to load: ";
                std::cin >> filename;
                phonebook.read_from_file(filename.c_str());
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                std::cout << "Invalid input. Please try again.\n";
                continue;
            }
        }
    }
    return 0;
}