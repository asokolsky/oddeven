#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>
//#include <execinfo.h>

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

vector <pair<char, int>> expresions; 
deque <char> output; 

/** push back the string into the output */
void push_back(const string s)
{
  for(auto ch: s)
    output.push_back(ch);
}

int priority(char op)
{
  if(op == 0)
    return 100;
  else if(op == '*' || op == '/')
    return 90;
  return 80;
}


int main() 
{
  int val;
  cin >> val;
  expresions.push_back({0, val});
  int ops;
  cin >> ops;
  for(int i = 0; i < ops; i++)
  {
    string op;
    cin >> op >> val;
    expresions.push_back({op[0], val});
  }

  // now print 'expresions' into output
  int iContextPriority = 0;
  for(auto elt: expresions)
  {
    int iThisPriority = priority(elt.first);
    if((iThisPriority > iContextPriority) && !output.empty())
    {
      output.push_front('(');
      output.push_back(')');
    }
    if(elt.first != 0)
    {
      output.push_back(' ');
      output.push_back(elt.first);
      output.push_back(' ');
    }
    push_back(to_string(elt.second));
    iContextPriority = iThisPriority;
  }
  // now print 'output' into cout
  for(auto ch: output)
    cout << ch;

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
