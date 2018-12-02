#include <iostream>
#include <string>
#include <vector>

using namespace std;

// базовый класс для классов студента, учителя и полицейского
class Person
{
public:
    Person (const string& inputName, const string& inputInfo)
    {
        personName = inputName;
        addInfo = inputInfo;
    }

    virtual void Walk (const string& destination) const
    {
        // убрал двоеточие после типа занятия, чтобы выглядело по-человечнее
        cout <<  professionType << " " << personName << " walks to " << destination << endl;
    }

    // защита от случайного изменения неконстаного элемента personName
    string GetName() const
    {
        return personName;
    }

    // защита от случайного изменения неконстаного элемента professionType
    string GetProfession() const
    {
        return professionType;
    }

protected:
    // элемент professionType нужен, чтобы не переопределять метод Walk() внутри классов полицейского и учителя
    // для полицейского и учителя метод Walk() идентичен
    string professionType = "none";
    string personName;
    // addInfo - дополнительное поле нужное для констркуторов классов студента и учителя
    string addInfo;
};

class Student : public Person
{
public:
    // в данном классе используем поле addInfo для хранения названия песни
    Student (const string& inputName, const string& inputSongName) : Person(inputName, inputSongName)
    {
        professionType = "Student";
    }

    void Walk (const string& destination) const override // переопределяем метод так как, в отличие от полицейского и учителя, студент поет (метод Sing()) когда идет куда-либо
    {
        cout <<  professionType << " " << personName << " walks to " << destination << endl;
        SingSong();
    }

    void SingSong() const // уникальный метод класса студента
    {
        cout << professionType << " " << personName << " sings a song \"" << addInfo << "\""<< endl;
    }
};

class Teacher : public Person
{
public:
    // используем поле addInfo для хранения названия предмета
    Teacher (const string& inputName, const string& inputSubjectName) : Person(inputName, inputSubjectName)
    {
        professionType = "Teacher";
    }

    // метод Walk() определен в базовом классе

    void Teach() const // уникальный метод класса учителя
    {
        cout << professionType << " " << personName << " teaches " << addInfo << endl;
    }
};


class Policeman : public Person
{
public:
    // поле addInfo не используется
    explicit Policeman (const string& inputName) : Person(inputName, "")
    {
        professionType = "Policeman";
    }

    // метод Walk() определен в базовом классе

    void Check (const Person& person) const // уникальный метод класса полицеского
    {
        cout << professionType << " " << personName << " checks " << person.GetProfession() << ". " <<
        person.GetProfession() << "'s name is " << person.GetName() << endl;
    }
};

void VisitPlaces (const Person& person, const vector<string>& places)
{
    for (const auto& place : places) person.Walk(place);
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
