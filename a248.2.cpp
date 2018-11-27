#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Часть 2. Без лишних скобок

Модифицируйте решение предыдущей части так, чтобы предыдущее выражение обрамлялось скобками лишь при необходимости, 
то есть только в том случае, когда очередная операция имеет бо́льший приоритет, чем предыдущая.

op priority
0  100
*  90
/  90
+  80
-  80


*/

struct Expression
{
  /** one of +,-,*,/,0 the latter being for number stored in value field */
  char op;
  union {
    Expression *left;
    int value;
  };
  Expression *right;

  //Expression() : op(0), left(0), right(0) {}
  Expression(int val) : op(0), value(val), right(0) {}
  Expression(char o, Expression *l, Expression *r) : op(o), left(l), right(r) {}
  ~Expression()
  {
    if(op != 0)
    {
      delete left;
      left = 0;
      delete right;
      right = 0;
    }
  }

  int priority()
  {
    if(op == 0)
      return 100;
    else if(op == '*' || op == '/')
      return 90;
    return 80;
  }

  void print(int iContextPriority = 0)
  {
    if(op == '0')
    {
      // we are just an integer
      cout << to_string(value);
    }
    else
    {
      int iThisPriority = priority();
      if(iThisPriority < iContextPriority) cout << "(";
      left->print(iThisPriority);
      cout << " " << op << " ";
      right->print(iThisPriority);
      if(iThisPriority < iContextPriority) cout << ")";
    }
  }
};

int main() 
{
  int val;
  cin >> val;
  Expression *pRoot = new Expression(val);
  int ops;
  cin >> ops;
  for(int i = 0; i < ops; i++)
  {
    string op;
    cin >> op >> val;
    switch(op[0])
    {
      case '+':
      case '-':
      case '/':
      case '*':
        pRoot = new Expression(op[0], pRoot, new Expression(val));
        break;
      default:
        break;
    }
  }
  pRoot->print();
  delete pRoot;
  pRoot = 0;
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
(8 * 3 - 6) / 1
*/
