#pragma once
#include <iostream>
#include <sstream>

using namespace std;

class Date 
{
public:
  Date() : _y(0), _m(0), _d(0) {} 
  Date(int y, int m, int d);

  int GetYear() const { return _y; }
  int GetMonth() const { return _m; }
  int GetDay() const { return _d; }

private:
  int _y;
  int _m;
  int _d;
};

bool operator<(const Date& lhs, const Date& rhs);
inline bool operator>=(const Date& lhs, const Date& rhs) {
  return !(lhs < rhs);
}
bool operator>(const Date& lhs, const Date& rhs);
inline bool operator<=(const Date& lhs, const Date& rhs) {
  return !(lhs > rhs);
}
bool operator==(const Date& lhs, const Date& rhs);
inline bool operator!=(const Date& lhs, const Date& rhs) {
  return !(lhs == rhs);
}
std::ostream& operator<<(std::ostream& os, const Date &obj);
std::istream& operator>>(std::istream& is, Date &obj);

Date ParseDate(std::istream& is);
