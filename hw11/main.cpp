#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pet {
private:
    string name;
    int age;
    int weight;
    int limbs_num;
public:
    Pet() : name(""), age(0), weight(0), limbs_num(0) {}

    Pet(string name, int age, int weight, int limbs_num) : name(name), age(age), weight(weight),
                                                           limbs_num(limbs_num) {}

    int get_age() { return age; }

    string get_name() { return name; }
};

class Dog : public Pet {
private:
    string collar_color;
    string fur_color;
public:
    Dog() : Pet(), collar_color(""), fur_color("") {}

    Dog(string name, int age, int weight, int limbs_num, string collar_color, string fur_color) :
            Pet(name, age, weight, limbs_num), collar_color(collar_color), fur_color(fur_color) {}

    int get_age_in_dog_years() {
        return this->get_age() * 7;
    }

    string get_fur_color() {
        return fur_color;
    }

    void print_info() {
        cout << this->get_name() << " is a Dog that is " << this->get_age() << " years old." << endl;
        cout << "That is " << get_age_in_dog_years() << " years in dog-years. " << endl;
        cout << "It's fur color is " << get_fur_color() << "." << endl;
    }
};

class Cat : public Pet {
private:
    string eye_color;
    int lives_left;
public:
    Cat() : Pet(), eye_color(""), lives_left(9) {}

    Cat(string name, int age, int weight, int limbs_num, string eye_color, int lives_left) :
            Pet(name, age, weight, limbs_num), eye_color(eye_color), lives_left(lives_left) {}

    void print_info() {
        cout << this->get_name() << " is a Cat that is " << this->get_age() << " years old." << endl;
        cout << "It has " << eye_color << " eyes and " << lives_left << " lives left." << endl;
    }
};

class Parrot : public Pet {
private:
    vector<string> spoken_languages;
    int bad_words_known_amount;
public:
    Parrot() : Pet(), spoken_languages(), bad_words_known_amount(0) {}

    Parrot(string name, int age, int weight, int limbs_num, vector<string> languages, int bad_words) :
            Pet(name, age, weight, limbs_num), spoken_languages(languages), bad_words_known_amount(bad_words) {}

    void print_info() {
        cout << this->get_name() << " is a Parrot that is " << this->get_age() << " years old." << endl;
        cout << "It knows " << bad_words_known_amount << " bad words and speaks: ";
        for (const string &lang: spoken_languages) {
            cout << lang << " ";
        }
        cout << endl;
    }
};

int main() {
    Dog d("Rover", 3, 20, 4, "Red", "Golden");
    Cat c("Mittens", 4, 10, 4, "Green", 7);
    Parrot p("Polly", 2, 1, 2, {"English", "Spanish"}, 5);

    d.print_info();
    c.print_info();
    p.print_info();

    return 0;
}
