#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Часть 1

Реализуйте построение арифметического выражения согласно следующей схеме:

    изначально есть выражение, состоящее из некоторого целого числа x;
    на каждом шаге к текущему выражению применяется некоторая операция: 
    прибавление числа, вычитание числа, умножение на число или деление на число; 
    перед применением операции выражение всегда должно быть заключено в скобки.

Пример

Изначально есть число 8, соответствующее выражение:
8
К нему применяется операция умножения на 3, получается выражение 
(8) * 3
Затем вычитается 6:
((8) * 3) - 6
Наконец, происходит деление на 1; итоговое выражение:
(((8) * 3) - 6) / 1

Формат ввода

В первой строке содержится исходное целое число x. 
Во второй строке содержится целое неотрицательное число N— количество операций. 
В каждой из следующих N строк содержится очередная операция:

    прибавление числа a: + a;
    либо вычитание числа b: - b;
    либо умножение на число c: * c;
    либо деление на число d: / d.

Количество операций может быть нулевым — в этом случае необходимо вывести исходное число.
Формат вывода

Выведите единственную строку — построенное арифметическое выражение.

Обратите внимание на расстановку пробелов вокруг символов:

    каждый символ бинарной операции (+, -, * или /) должен быть окружён ровно одним пробелом с каждой стороны: (8) * 3;
    символ унарного минуса (для отрицательных чисел) не нуждается в дополнительном пробеле: -5;
    скобки и числа не нуждаются в дополнительных пробелах.

Подсказка

Для преобразования числа к строке используйте функцию to_string из библиотеки <string>.


*/

struct Expression
{
  /** one of +,-,*,/,0,1 the latter being for number or (number) stored in value field */
  char op;
  union {
    Expression *left;
    int value;
  };
  Expression *right;

  //Expression() : op(0), left(0), right(0) {}
  Expression(int val, bool bInBraces = false) : op(bInBraces ? 1 : 0), value(val), right(0) {}
  Expression(char o, Expression *l, Expression *r) : op(o), left(l), right(r) {}

  void print(bool bNeedsParenthesis = true)
  {
    if(op == 0)
    {
      // we are just an integer
      cout << to_string(value);
    }
    else if(op == 1)
    {
      // we are just an (integer)
      if(!bNeedsParenthesis)
        cout << to_string(value);
      else
        cout << "(" << to_string(value) << ")";
    }
    else
    {
      if(bNeedsParenthesis) cout << "(";
      left->print();
      cout << " " << op << " ";
      right->print();
      if(bNeedsParenthesis) cout << ")";
    }
  }
  int evaluate()
  {

  }
};

int main() 
{
  int val;
  cin >> val;
  Expression *pRoot = new Expression(val, true);
  int ops;
  cin >> ops;
  for(int i = 0; i < ops; i++)
  {
    string op;
    cin >> op >> val;
    pRoot = new Expression(op[0], pRoot, new Expression(val));

  }
  pRoot->print(false);
  cout << endl;
  return 0;
}


/*
Ввод
8
3
* 3
- 6
/ 1

Вывод
(((8) * 3) - 6) / 1
*/
