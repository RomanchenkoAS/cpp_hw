#include "phonebook.h"
#include <cstring> // strlen
#include <iostream>

int main(void) {
    Phonebook phonebook;

    while (true) {
        std::string firm_title, owner_name, number_mobile, info;
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
                std::cout << "Firm title:\t\t";
                std::getline(std::cin, firm_title);
                std::cout << "Owner name:\t";
                std::getline(std::cin, owner_name);
                std::cout << "Mobile number:\t";
                std::getline(std::cin, number_mobile);
                std::cout << "Info:\t\t";
                std::getline(std::cin, info);
                std::string add_line = firm_title + "; " + owner_name + "; " +
                                       number_mobile + "; " + info + "; ";
                phonebook.add(add_line.c_str());
                break;
            }
            case 3: {
                std::cin.ignore();
                std::cout << "Enter firm title to delete: ";
                std::getline(std::cin, firm_title);
                if (phonebook.delete_firm(firm_title.c_str()) != 0) {
                    std::cout << "Firm was not found.\n";
                };
                break;
            }
            case 4: {
                std::cin.ignore();
                std::cout << "Enter firm title to find: ";
                std::getline(std::cin, firm_title);
                int position = phonebook.find_firm(firm_title.c_str());
                if (position == -1) {
                    std::cout << "Firm " << firm_title << " was not found\n";
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