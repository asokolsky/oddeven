#include <iostream>
#include <vector>
#include <string>


using namespace std;

/**
 * У каждого из нас есть ежемесячные дела, 
 * каждое из которых нужно выполнять в конкретный день каждого месяца: 
 * оплата счетов за электричество, абонентская плата за связь и пр. 
 * Вам нужно реализовать работу со списком таких дел, а именно, обработку следующих операций:
 * 
 * ADD i s
 * Добавить дело с названием s в день i.
 * 
 * NEXT
 * Закончить текущий месяц и начать новый. 
 * Если новый месяц имеет больше дней, чем текущий, добавленные дни изначально не будут содержать дел. 
 * Если же в новом месяце меньше дней, дела со всех удаляемых дней необходимо будет переместить на последний день нового месяца.
 * 
 * Обратите внимание, что количество команд этого типа может превышать 11.
 * 
 * DUMP i
 * Вывести все дела в день i.
 * 
 * Изначально текущим месяцем считается январь. 
 * Количества дней в месяцах соответствуют Григорианскому календарю с той лишь разницей, что в феврале всегда 28 дней.
 * 
 */
/*void removeTrailingSpaces(string &str)
{
  while(str.size() > 0)
  {
    if(str[str.size() - 1] == ' ')
      str.pop_back();
    else
      break;
  }
}*/

// string can have words separated by ' '.  Ignore the trailing occurance
int countWords(const string &str)
{
  if(str.size() == 0)
    return 0;
  int iSpaces = 0;
  for(size_t pos = 0; pos != string::npos; pos++) 
  {
    pos = str.find(' ', pos);
    if(pos == (str.size() - 1))
      break;
    iSpaces++;
  }
  return iSpaces + 1;
}

void dump(const string &str)
{
  int iWords = countWords(str);
  cout << iWords;
  if(iWords > 0)
    cout << " " << str;
  cout << endl;
}

void dump(int iMonth, vector <string> tasks)
{
  for(int i = 0; i < tasks.size(); ++i)
  {
    cout << iMonth << ":" << (i+1) << ":";
    dump(tasks[i]);
  }
}

int main()
{
  vector <int> vDaysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  
  int iCurrentMonth = 0;
  vector <string> tasks;
  tasks.resize(vDaysInMonth[iCurrentMonth], "");

  int ops;
  cin >> ops;
  for(int i = 0; i < ops; ++i)
  {
    string cmd;
    cin >> cmd;
    if(cmd == "QUIT")
    {
      dump(iCurrentMonth, tasks);
      break;
    }
    else if(cmd == "NEXT")
    {
      if(++iCurrentMonth >= vDaysInMonth.size())
        iCurrentMonth = 0;
      int iNextMonthDays = vDaysInMonth[iCurrentMonth];
      if(iNextMonthDays < tasks.size())
      {
        for(int i = iNextMonthDays; i < tasks.size(); ++i)
        {
          if(tasks[i].size() != 0)
          {
            string a = tasks[iNextMonthDays - 1]; // '' or 'foo '
            string b = tasks[i]; // 'bar '
            tasks[iNextMonthDays - 1] = a + b;
          }
        }
        //dump(tasks[iNextMonthDays - 1]);
      }
      tasks.resize(iNextMonthDays, "");
      continue;
    }
    int iArg;
    cin >> iArg;
    if(cmd == "DUMP")
    {
      if(iArg > tasks.size())
        dump(iCurrentMonth, tasks);
      else
        dump(tasks[iArg-1]);
    }
    else if(cmd == "ADD")
    {
      string strArg;
      cin >> strArg;
      tasks[iArg-1] += strArg + " ";
    }
  }
  return 0;
}
