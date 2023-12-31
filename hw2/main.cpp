/*
 * Создайте приложение "Телефонная книга". Необходимо хранить
 * данные об абоненте (ФИО, домашний телефон, рабочий телефон,
 * мобильный телефон, дополнительная информация о контакте) внутри
 * соответствующего класса. Наполните класс переменными-членами,
 * функциями-членами, конструкторами, inline-функциями-членами,
 * используйте инициализаторы, реализуйте деструктор.
 * Обязательно необходимо выделять динамически память под ФИО.
 * Предоставьте пользователю возможность добавлять новых абонентов,
 * удалять абонентов, искать абонентов по ФИО, показывать всех абонентов,
 * сохранять информацию в файл и загружать из файла.
 */

#include "phonebook.h"
#include <cstring> // strlen
#include <iostream>

int main(void) {
    // testing();
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
            std::cout << "Enter name to delete: ";
            std::getline(std::cin, name);
            if (phonebook.delete_person(name.c_str()) != 0) {
                std::cout << "Person was not found.\n";
            };
            break;
        }
        case 4: {
            std::cin.ignore();
            std::cout << "Enter name to find: ";
            std::getline(std::cin, name);
            int position = phonebook.find_person(name.c_str());
            if (position == -1) {
                std::cout << "Person " << name << " was not found\n";
            } else {
                Person *found = phonebook.get_person(position);
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
            std::cout << std::endl;
        }
    }
    return 0;
}