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
Вспомним класс Rational, который мы реализовали в задачах, посвящённых перегрузке операторов. 
Там специально говорилось, что в тестах объекты класса Rational никогда не создаются с нулевым знаменателем 
и никогда не выполняется деление на ноль. Настало время избавиться от этого ограничения и научиться 
обрабатывать нулевой знаменатель и деление на ноль. В этой задаче вам предстоит это сделать.

Поменяйте реализацию конструктора класса Rational так, чтобы он выбрасывал исключение invalid_argument, 
если знаменатель равен нулю. Кроме того, переделайте реализацию оператора деления для класса Rational так, 
чтобы он выбрасывал исключение domain_error, если делитель равен нулю.

Напомним, что вам надо реализовать интерфейс

class Rational {
public:
  Rational();
  Rational(int numerator, int denominator);

  int Numerator() const;
  int Denominator() const;
};

и оператор деления для класса Rational
operator / (const Rational& lhs, const Rational& rhs);

Так же, как и в задачах на перегрузку операторов, вам будет предложен файл с заготовкой кода. 
Функция main в этом файле содержит ряд юнит-тестов, которые позволят вам проверить свою реализацию. 
При проверке вашего решения оно будет тестироваться на более полном наборе тестов, так что успешное 
прохождение всех юнит-тестов не гарантирует, что ваша реализация будет зачтена.

Шаблон программы:

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
/*
int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
*/