#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>


using namespace std;

/**
Часть 5

Наконец, вам нужно реализовать возможность использовать объекты класса Rational в качестве элементов контейнера set и ключей в контейнере map. 
Пример:
set<Rational> rationals;
rationals.insert(Rational(1, 2));
rationals.insert(Rational(1, 3));

map<Rational, string> name;
name[Rational(1, 2)] = "одна вторая";
 * 
 */

static int gcd(int a, int b)
{
  return (b == 0) ? a : gcd(b, a%b);
}

class Rational 
{
public:
  Rational() : _n(0), _d(1) {}

  Rational(int numerator, int denominator) : _n(numerator), _d(denominator) 
  {
    normalize();
  }

  int Numerator() const { return _n; }
  int Denominator() const { return _d; }

  Rational operator+(const Rational &rhs) const
  {
    int n = rhs.Numerator();
    int d = rhs.Denominator();
    Rational res((_n*d) + (_d*n), _d*d);
    return res;
  }
  Rational operator-(const Rational &rhs) const
  {
    int n = rhs.Numerator();
    int d = rhs.Denominator();
    Rational res((_n*d) - (_d*n), _d*d);
    return res;
  }
  Rational operator*(const Rational &rhs) const
  {
    Rational res(_n*rhs.Numerator(), _d*rhs.Denominator());
    return res;
  }  
  Rational operator/(const Rational &rhs) const
  {
    Rational res(_n*rhs.Denominator(), _d*rhs.Numerator());
    return res;
  }  

private:
  void normalize()
  {
    if(_n == 0)
      _d = 1;
    else if(_d < 0)
    {
      _n = -_n;
      _d = -_d;
    }
    int i = gcd(abs(_n), _d);
    _n = _n/i;
    _d = _d/i;
  }
  int _n;
  int _d;
};

inline bool operator==(const Rational &lhs, const Rational &rhs) 
{
  return (lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator());
}
inline bool operator<(const Rational &lhs, const Rational &rhs) 
{
  return (lhs.Numerator() * rhs.Denominator()) < (lhs.Denominator() * rhs.Numerator());
}

std::ostream& operator<<(std::ostream& os, const Rational &obj)
{
  os << obj.Numerator() << "/" << obj.Denominator();
  return os;
}
std::istream& operator>>(std::istream& is, Rational &obj)
{
  int n,d;
  char ch;
  is >> n >> ch >> d;
  Rational res(n,d);
  // read obj from stream
  if(ch != '/')
    is.setstate(std::ios::failbit);
  else
    obj = res;
  return is;
}

/*
int main()
{
  {
    const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
    if (rs.size() != 3) {
        cout << "Wrong amount of items in the set" << endl;
        return 1;
    }

    vector<Rational> v;
    for (auto x : rs) {
        v.push_back(x);
    }
    if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
        cout << "Rationals comparison works incorrectly" << endl;
        return 2;
    }
  }

  {
      map<Rational, int> count;
      ++count[{1, 2}];
      ++count[{1, 2}];

      ++count[{2, 3}];

      if (count.size() != 2) {
          cout << "Wrong amount of items in the map" << endl;
          return 3;
      }
  }

  cout << "OK" << endl;
}
*/