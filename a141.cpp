#include <iostream>
#include <string>

using namespace std;

/**
Дана структура LectureTitle:
 * 
 */
struct Specialization {
  string _val;
  explicit Specialization(const char *p) : _val(p) {}
};
struct Course {
  string _val;
  explicit Course(const char *p) : _val(p) {}
};
struct Week {
  string _val;
  explicit Week(const char *p) : _val(p) {}
};
struct LectureTitle {
  string specialization;
  string course;
  string week;

  LectureTitle(const Specialization &s, const Course &c, const Week &w) :
    specialization(s._val), course(c._val), week(w._val)
  {
  }

};

/*
Допишите конструктор и структуры Specialization, Course, Week так, чтобы объект LectureTitle можно было создать с помощью кода 

LectureTitle title(
    Specialization("C++"),
    Course("White belt"),
    Week("4th")
);

но нельзя было с помощью следующих фрагментов кода:
LectureTitle title("C++", "White belt", "4th");

LectureTitle title(string("C++"), string("White belt"), string("4th"));

LectureTitle title = {"C++", "White belt", "4th"};

LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};

LectureTitle title(
    Course("White belt"),
    Specialization("C++"),
    Week("4th")
);

LectureTitle title(
    Specialization("C++"),
    Week("4th"),
    Course("White belt")
);

*/

/*
int main() 
{
LectureTitle title(Specialization("C++"), Course("White belt"), Week("4th"));

LectureTitle title(string("C++"), string("White belt"), string("4th"));

LectureTitle title = {"C++", "White belt", "4th"};

LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};

LectureTitle title(
    Course("White belt"),
    Specialization("C++"),
    Week("4th")
);

LectureTitle title(
    Specialization("C++"),
    Week("4th"),
    Course("White belt")
);
  return 0;
}
*/
