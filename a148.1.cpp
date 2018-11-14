#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>


using namespace std;

/**
Часть 1

В первой части вам надо реализовать класс Rational, который представляет собой рациональное число вида p/q, 
где p целое, а q натуральное. Он должен иметь следующий интерфейс:

class Rational {
public:
  Rational();
  Rational(int numerator, int denominator);

  int Numerator() const;
  int Denominator() const;
};

Класс Rational должен гарантировать, что p/q — это несократимая дробь. Например, код
Rational r(4, 6);
cout << r.Numerator() << '/' << r.Denominator();
должен выводить «2/3» — именно поэтому мы делаем Rational классом, а не структурой. 

Структура позволила бы нарушить этот инвариант: 
struct Rational {
    int numerator, denominator;
};
Rational r{2, 3};
r.numerator = 6; // Нарушен инвариант несократимости

Список требований, предъявляемых к реализации интерфейса класса Rational:

    Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
    При конструировании объека класса Rational с параметрами p и q должно выполняться сокращение дроби p/q 
    (здесь вам может пригодиться решение задачи «Наибольший общий делитель»).
    Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный числитель и положительный знаменатель.
    Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные числитель и знаменатель (обратите внимание на случай Rational(-2, -3)).
    Если числитель дроби равен нулю, то знаменатель должен быть равен 1.

Гарантируется, что ни в одном из тестов, на которых будет тестироваться ваша реализация, не будет знаменателя, равного нулю.

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
/*
int main() 
{
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
*/
