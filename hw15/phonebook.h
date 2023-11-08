#pragma once
#include <iostream>
#define delimiter "\n------------------\n"

int get_int(std::string message);
void testing();

class Firm {
  private:
    char *title, *owner_name, *number, *info;
    void create_field(char *&field, const char *input_line);

  public:
    Firm();
    Firm(const char *name, const char *number_work, const char *number_mobile,
         const char *info);
    Firm(Firm const &firm);
    ~Firm();
    Firm &operator=(const Firm &other);
    void set_name(const char *input);
    void set_number_work(const char *input);
    void set_number(const char *input);
    void set_info(const char *input);
    const char *get_name() const { return title; }
    const char *get_owner_name() const { return owner_name; }
    const char *get_number() const { return number; }
    const char *get_info() const { return info; }
    void print();
    void print_summary();
    std::string get_summary() const;
};

class Phonebook {
  private:
    Firm *content;
    int length;

  public:
    Phonebook();
    Phonebook(std::initializer_list<Firm> init_list);
    ~Phonebook();
    void add(Firm const &new_firm);
    void add(const char *input_line);
    int find_firm(const char *name);
    int delete_firm(const char *name);
    Firm *get_firm(int index) const;
    void print(bool summary = false) const;
    int save_to_file(const char *filename);
    int read_from_file(const char *filename, bool clear = false);
};