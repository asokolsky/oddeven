#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <stdexcept>

using namespace std;

/**
Итак, теперь у нас с вами есть полноценный тип для представления обыкновенных дробей: 
класс Rational интегрирован в язык с помощью перегрузки операторов и не позволяет выполнять 
некорректные операции за счёт выбрасывания исключений. Давайте на основе класса Rational 
создадим простой калькулятор для обыкновенных дробей.

Вам надо написать программу, которая считывает из стандартного ввода одну строку в формате 
ДРОБЬ_1 операция ДРОБЬ_2. 
ДРОБЬ_1 и ДРОБЬ_2 имеют формат X/Y, где X — целое, а Y — целое неотрицательное число. 
операция — это один из символов '+', '-', '*', '/'.

Если ДРОБЬ_1 или ДРОБЬ_2 является некорректной обыкновенной дробью, 
ваша программа должна вывести в стандартный вывод сообщение "Invalid argument". 
Если считанная операция — это деление на ноль, выведите в стандартный вывод сообщение "Division by zero". 
В противном случае выведите результат операции.

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
    if(_d == 0)
      throw invalid_argument("0 as denominator");
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
    if(rhs.Numerator() == 0)
      throw domain_error("Division by 0");
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

int main() 
{
  while(cin)
  {
    Rational l, r, res;
    string op;
    try {
      cin >> l >> op >> r;
    } catch(invalid_argument &x) {
      cout << "Invalid argument" << endl;
      continue;
    }
    if(op == "+")
    {
      res = l + r;
    }
    else if(op == "-")
    {
      res = l - r;
    }
    else if(op == "*")
    {
      res = l * r;
    }
    else if(op == "/")
    {
      try {
      res = l / r;
      } catch (domain_error &err) {
        cout << "Division by zero" << endl;
        continue;
      }
    }
    else
      break;
    cout << res << endl;
  }
  return 0;
}

/*

stdin
1/2 + 1/3
1/2 + 5/0
4/5 / 0/8

stdout
5/6
Invalid argument
Division by zero
*/