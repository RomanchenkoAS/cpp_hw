#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class FilerBase {
private:
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

    virtual void open_file(const string &filename) {
        file.open(filename);
        if (!file) {
            throw runtime_error("Failed to open " + filename);
        }
    };

    virtual void print() {
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

class FilerAscii : FilerBase {

};

int main() {
    FilerBase f1;
    f1.open_file("hw12/output/file.txt");
    f1.print();

}