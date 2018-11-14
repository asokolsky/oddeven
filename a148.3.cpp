#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>


using namespace std;

/**
Часть 3

Аналогично предыдущей части, реализуйте операторы * и /. Например, следующий код должен быть валидным: 
const Rational r = Rational(1, 2) * Rational(1, 3) / Rational(1, 4);
if (r == Rational(2, 3)) {
  cout << "equal";
}
Гарантируется, что ни в одном из тестов, на которых будет тестироваться ваша реализация, не будет выполняться деление на ноль.

 * 
 */

static int gcd(int a, int b)
{
  if(b == 0)
    return a;
  return gcd(b, a%b);
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
/*
int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
*/