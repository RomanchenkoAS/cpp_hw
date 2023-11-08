#pragma once
#include <iostream>
#define delimiter "\n------------------\n"

int get_int(std::string message);
void testing();

class Person {
  private:
    char *name, *number_work, *number_mobile, *info;
    void create_field(char *&field, const char *input_line);

  public:
    Person();
    Person(const char *name, const char *number_work, const char *number_mobile,
           const char *info);
    Person(Person const &source_person);
    ~Person();
    Person &operator=(const Person &other);
    void set_name(const char *input);
    void set_number_work(const char *input);
    void set_number_mobile(const char *input);
    void set_info(const char *input);
    const char *get_name() const { return name; }
    const char *get_number_work() const { return number_work; }
    const char *get_number_mobile() const { return number_mobile; }
    const char *get_info() const { return info; }
    void print();
    void print_summary();
    std::string get_summary() const;
};

class Phonebook {
  private:
    Person *content;
    int length;

  public:
    Phonebook();
    Phonebook(std::initializer_list<Person> init_list);
    ~Phonebook();
    void add(Person const &new_person);
    void add(const char *input_line);
    int find_person(const char *name);
    int delete_person(const char *name);
    Person *get_person(int index) const;
    void print(bool summary = false) const;
    int save_to_file(const char *filename);
    int read_from_file(const char *filename, bool clear = false);
};