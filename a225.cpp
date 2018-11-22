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
    считает пустую строку палиндромом;
    считает строку из одного символа палиндромом;
    осуществляет обычное сравнение символов на равенство, не игнорируя никакие символы, в том числе пробельные.

При разработке тестов подумайте, какие ошибки можно допустить при реализации функции IsPalindrom. Примеры ошибок:

    игнорируется первый или последний символ;
    сравнение соответствующих символов завершается не в середине строки, а раньше;
    игнорируются пробелы

  */

bool IsPalindrom(const string& s) {
  if(s.size() == 0)
    return true;
  int iHalfLength = s.size() / 2;
  for(int i = 0; i < iHalfLength ; ++i)
    if(s[i] != s[s.size() - 1 - i])
      return false;
}

void TestEmpty()
{
  Assert(IsPalindrom(""), to_string(__LINE__));
}
void TestOdd()
{
  Assert(IsPalindrom("x"), to_string(__LINE__));
  Assert(IsPalindrom("axa"), to_string(__LINE__));
  Assert(!IsPalindrom("abc"), to_string(__LINE__));

  Assert(IsPalindrom("madam"), to_string(__LINE__));
  Assert(IsPalindrom("level"), to_string(__LINE__));
  Assert(IsPalindrom("wasitacaroracatisaw"), to_string(__LINE__));
}
void TestEven()
{
  Assert(IsPalindrom("xx"), to_string(__LINE__));
  Assert(IsPalindrom("aa"), to_string(__LINE__));
  Assert(!IsPalindrom("ab"), to_string(__LINE__));
  Assert(IsPalindrom("abba"), to_string(__LINE__));
  Assert(!IsPalindrom("abbc"), to_string(__LINE__));
  Assert(!IsPalindrom("abca"), to_string(__LINE__));
}
void TestSpaces()
{
  Assert(IsPalindrom("\r\r"), to_string(__LINE__));
  Assert(!IsPalindrom("\r\n"), to_string(__LINE__));
  Assert(IsPalindrom("b\raa\rb"), to_string(__LINE__));
  Assert(!IsPalindrom("b\raa\nb"), to_string(__LINE__));
}

int main() {
  TestRunner runner;
  runner.RunTest(TestEmpty, "TestEmpty");
  runner.RunTest(TestOdd, "TestOdd");
  runner.RunTest(TestEven, "TestEven");
  runner.RunTest(TestSpaces, "TestSpaces");
  return 0;
}
