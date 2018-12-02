#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include <map>

using namespace std;

/**
 * Решите задачу «Имена и фамилии — 1» более эффективно, 
 * использовав двоичный поиск в методе Person::GetFullName. Напомним условие задачи.

Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.

*/

// Возвращает пустую строку, если имя неизвестно
string FindNameByYear(const map<int, string>& names, int year) {
  auto iter_after = names.upper_bound(year);
  string name;
  if (iter_after != names.begin()) {
    name = (--iter_after)->second;
  }
  return name;
}


class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";
    } else {
      return first_name + " " + last_name;
    }
  }
private:
  map<int, string> first_names;
  map<int, string> last_names;
};


/**
 * Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени. При этом с течением времени могут открываться всё новые факты из прошлого человека, поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.

Гарантируется, что все имена и фамилии непусты.

Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и фамилию человека по состоянию на конец данного года.

    Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
    Если к данному году случилось изменение фамилии, но не было ни одного изменения имени, верните "last_name with unknown first name".
    Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, верните "first_name with unknown last name".
*/

int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}

/*
Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria Sergeeva
Polina Volkova
Appolinaria Volkova
*/
