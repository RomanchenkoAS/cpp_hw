#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class FilerBase {
private:
    ifstream file;
public:
    virtual void open_file(const string &filename) {
        file.open(filename);
    };

    virtual void print() {};
};

int main() {

    return 0;
}