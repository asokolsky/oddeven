#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>


using namespace std;

/**
Часть 2

Реализуйте для класса Rational операторы ==, + и - так, чтобы операции с дробями можно было записывать естественным образом. 
Например, следующий код должен быть валидным: 
const Rational r = Rational(1, 2) + Rational(1, 3) - Rational(1, 4);
if (r == Rational(7, 12)) {
  cout << "equal";
}

 * 
 */

int gcd(int a, int b)
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
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
*/
