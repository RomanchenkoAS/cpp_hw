#include <iostream>
#include <string>
#include <fstream>
#include <bitset>

using namespace std;

class FilerBase {
private:
    ifstream file;

protected:
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

class FilerAscii : public FilerBase {
private:
    void print_char(char output) override {
        cout << (int) output << " ";
    };
};

class FilerBinary : public FilerBase {
private:

    void print_char(char output) override {
        cout << bitset<8>(output).to_string() << " ";
    };
};

int main() {
    cout << "Read file as plain text: " << endl;
    {
        FilerBase f1;
        f1.open_file("hw12/file.txt");
        f1.print();
    }

    cout << "\nRead file in ASCII codes: " << endl;
    {
        FilerAscii f2;
        f2.open_file("hw12/file.txt");
        f2.print();
    }

    cout << "\nRead file in binary digits: " << endl;
    {
        FilerBinary f3;
        f3.open_file("hw12/file.txt");
        f3.print();
    }
}