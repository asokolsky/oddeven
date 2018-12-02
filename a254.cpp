#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
В данном задании вам предстоит изменить код таким образом, чтобы он соответствовал изложенным в курсе принципам.
Представьте, что этот код вам достался в наследство от коллеги и теперь вам предстоит поддерживать его и улучшать. 

Первое, что вы решили сделать — это провести рефакторинг.

Конечные цели рефакторинга:
    упростить дальнейшую поддержку кода;
    уменьшить сложность кода;
    упростить добавление новых абстракций в программу.

Review criteria

Задание будет оцениваться по следующим критериям:
    эффективность выполнения кода;
    задублированность кода;
    эффективность использования приёмов рефакторинга кода, показанных в лекциях.

Кроме того, присылаемый вами код должен компилироваться.

 */

class Person
{
protected:  
  string Name;
public:
  Person(const string& name) : Name(name) {
  }
  virtual const char *type() const = 0;
  virtual void Walk(const string& destination) const {
    intro();
    cout << " walks to: " << destination << endl;
  }
  const char *getName() const {
    return Name.c_str();
  }
  void intro() const {
    cout << type() << ": " << Name;
  }
};

class Student : public Person {
  string FavouriteSong;
public:
  Student(const string& name, const string& favouriteSong) : 
    Person(name), FavouriteSong(favouriteSong) {    
  }
  const char *type() const {
    return "Student";
  }
  void Learn() {
    intro();
    cout << " learns" << endl;
  }
  void Walk(const string& destination) const {
    Person::Walk(destination);
    SingSong();
  }
  void SingSong() const {
    intro();
    cout << " sings a song: " << FavouriteSong << endl;
  }
};


class Teacher : public Person {
  string Subject;
public:
  Teacher(const string& name, const string& subject) : 
    Person(name), Subject(subject) {
  }
  const char *type() const {
    return "Teacher";
  }
  void Teach() {
    intro();
    cout << " teaches: " << Subject << endl;
  }
};

class Policeman : public Person {
public:
  Policeman(const string& name) : Person(name) {
  }
  const char *type() const {
    return "Policeman";
  }
  void Check(const Person& p) {
    intro();
    cout << " checks " << p.type() << ". " << p.type() << "'s name is: " << p.getName() << endl;
  }
};


void VisitPlaces(const Person& person, const vector<string>&places) {
  for (const auto& p : places)
    person.Walk(p);
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    
    const vector <string> places = {"Moscow", "London"};
    VisitPlaces(t, places);
    p.Check(s);
    VisitPlaces(s, places);
    return 0;
}
