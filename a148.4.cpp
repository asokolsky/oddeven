#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

/**
Часть 4

В этой части вам нужно реализовать операторы ввода и вывода для класса Rational. 
В результате у вас должен работать, например, такой код 
Rational r;
cin >> r;
cout << r;

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
std::ostream& operator<<(std::ostream& os, const Rational &obj)
{
  os << obj.Numerator() << "/" << obj.Denominator();
  return os;
}
std::istream& operator>>(std::istream& is, Rational &obj)
{
  if(is)
  {
    int n,d;
    char ch;
    is >> n >> ch >> d;
    Rational res(n,d);
    // read obj from stream
    if(ch != '/')
      ; //is.setstate(std::ios::failbit);
    else
      obj = res;
  }
  return is;
}

/*
int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}
*/