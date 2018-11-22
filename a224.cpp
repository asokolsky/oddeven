#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

/**
Список требований, предъявляемых к реализации интерфейса класса Rational:

    Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
    При конструировании объекта класса Rational с параметрами p и q должно выполняться сокращение дроби p/q.
    Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный числитель и положительный знаменатель.
    Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные числитель и знаменатель (обратите внимание на случай Rational(-2, -3)).
    Если числитель дроби равен нулю, то знаменатель должен быть равен 1.

Разработайте набор юнит-тестов, которые будут проверять корректность реализации класса Rational. Тестировать случай, когда знаменатель равен нулю, не надо.
*/

//#include "a14B.cpp"

/*class Rational 
{
public:
  // Вы можете вставлять сюда различные реализации,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный

  Rational();
  Rational(int numerator, int denominator) {
  }

  int Numerator() const {
  }

  int Denominator() const {
  }
};*/

void TestConstructor()
{
  Rational r;
  AssertEqual(r.Numerator(), 0, to_string(__LINE__));
  AssertEqual(r.Denominator(), 1, to_string(__LINE__));
}
void TestConstructor1()
{
  Rational r(6, 8);
  AssertEqual(r.Numerator(), 3, to_string(__LINE__));
  AssertEqual(r.Denominator(), 4, to_string(__LINE__));
}
void TestNegativity()
{
  Rational r(6, -8);
  AssertEqual(r.Numerator(), -3, to_string(__LINE__));
  AssertEqual(r.Denominator(), 4, to_string(__LINE__));
}
void TestPositivity()
{
  Rational r(-6, -8);
  AssertEqual(r.Numerator(), 3, to_string(__LINE__));
  AssertEqual(r.Denominator(), 4, to_string(__LINE__));
}
void Test0()
{
  Rational r(0, -6);
  AssertEqual(r.Numerator(), 0, to_string(__LINE__));
  AssertEqual(r.Denominator(), 1, to_string(__LINE__));
}


int main() {
  TestRunner runner;
  runner.RunTest(TestConstructor, "TestConstructor");
  runner.RunTest(TestConstructor1, "TestConstructor1");
  runner.RunTest(TestNegativity, "TestNegativity");
  runner.RunTest(TestPositivity, "TestPositivity");
  runner.RunTest(Test0, "Test0");
  return 0;
}

