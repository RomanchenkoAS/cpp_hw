#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class FilerBase {
private:
    ifstream file;
public:
    FilerBase() : file() {};

    ~FilerBase() {
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
                    cout << output;
                }
            } else {
                throw runtime_error("File is not open.");
            }
        } catch (const exception &e) {
            cerr << "Error: " << e.what() << std::endl;
        }
    }
};

int main() {
    FilerBase f1;
    f1.open_file("hw12/output/file.txt");
    f1.print();

}