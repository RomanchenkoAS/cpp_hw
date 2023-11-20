#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class FilerBase {
protected:
    ifstream file;

    virtual void print_char(char output) {
        /* Display a single character into console */
        cout << output;
    };
public:
    FilerBase() : file() {};

    virtual ~FilerBase() {
        if (is_open()) file.close();
    }

    bool is_open() { return (file.is_open()); }

    void open_file(const string &filename) {
        file.open(filename);
        if (!file) {
            throw runtime_error("Failed to open " + filename);
        }
    };

    void print() {
        char output = 0;
        try {
            if (is_open()) {
                while (file.get(output)) {
                    print_char(output);
                }
            } else {
                throw runtime_error("File is not open.");
            }
        } catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
};

class Mapper : public FilerBase {
private:
    string text_body;
    unordered_map<string, int> dictionary;
    pair<string, int> top_used_word;
public:
    void print_char(char output) override {
        cout << (int) output << " ";
    };

    void read_text() {
        char output = 0;
        try {
            if (is_open()) {
                while (file.get(output)) {
                    text_body += output;
                }
            } else {
                throw runtime_error("File is not open.");
            }
        } catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void compose_dictionary() {
        string word;
        top_used_word = {"", 0};
        for (char c: text_body) {
            if (isalpha(c) || c == '\'') {
                word += c;
            } else {
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                if (!word.empty()) {
                    if (dictionary.count(word) == 0) {
                        dictionary.insert({word, 1});
                    } else {
                        dictionary[word]++;
                    }
                    if (dictionary[word] > top_used_word.second) {
                        top_used_word = {word, dictionary[word]};
                    }
                }
                word.clear();
            }
        }
    }

    void show_dictionary() {
        for (auto it = dictionary.begin(); it != dictionary.end(); ++it) {
            std::cout << it->first << ": " << it->second << std::endl;
        }
    }

    pair<string, int> get_top_used_word() {
        return top_used_word;
    }

    string get_text_body() {
        return text_body;
    }
};

int main() {

    Mapper mapper;
//    SET CORRECT FILE PATH
    mapper.open_file("/home/artur/dev/cpp_hw/hw17/textfile");
    mapper.read_text();
    mapper.compose_dictionary();
    mapper.show_dictionary();
    pair<string, int> top_word = mapper.get_top_used_word();
    cout << "Top used word is \"" << top_word.first << "\" it has been used " << top_word.second << " times.\n";
    return 0;
}