#include <iostream>
#include <string>

using namespace std;

/**
Определите до конца тела классов, соблюдая следующие требования:

    Класс Dog должен являться наследником класса Animal.
    Конструктор класса Dog должен принимать параметр типа string и инициализировать им поле Name в классе Animal.

 */
class Animal {
public:
    Animal(const string &n) : Name(n) {
    }

    const string Name;
};


class Dog : public Animal
{
public:
    Dog(const string &n) : Animal(n) {
    }

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

