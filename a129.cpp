#include <iostream>
#include <vector>
#include <string>


using namespace std;

/**
 * Люди стоят в очереди, но никогда не уходят из её начала, зато могут приходить в конец и уходить оттуда. 
 * Более того, иногда некоторые люди могут прекращать и начинать беспокоиться из-за того, что очередь не продвигается.
 * 
 * Реализуйте обработку следующих операций над очередью:

    WORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
    QUIET i: пометить i-го человека как успокоившегося;
    COME k: добавить k спокойных человек в конец очереди;
    COME -k: убрать k человек из конца очереди;
    WORRY_COUNT: узнать количество беспокоящихся людей в очереди.

  * Изначально очередь пуста.
  * 
  * Формат ввода
  * Количество операций Q, затем описания операций.
  * Для каждой операции WORRY i и QUIET i гарантируется, что человек с номером i существует в очереди на момент операции.
  * Для каждой операции COME -k гарантируется, что k не больше текущего размера очереди.
  * 
  * Формат вывода
  * Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди.
  * 
  */

void worry(vector<int> &queue, int i)
{
  queue[i] = 1;
}
void quiet(vector<int> &queue, int i)
{
  queue[i] = 0;
}
void come(vector<int> &queue, int i)
{
  if(i > 0)
    for(;i > 0; --i)
      queue.push_back(0);
  else if(i < 0)
    for(i = -i; i > 0; --i)
      queue.pop_back();
}
int worry_count(const vector<int> &queue)
{
  int iRes = 0;
  for(auto i: queue)
    iRes += i;
  return iRes;
}

int main()
{
  vector<int> queue;
  int ops;
  cin >> ops;
  for(int i = 0; i < ops; ++i)
  {
    string cmd;
    cin >> cmd;
    if(cmd == "WORRY_COUNT")
    {
      cout << worry_count(queue) << endl;
      continue;
    }
    int iArg;
    cin >> iArg;
    if(cmd == "COME")
      come(queue, iArg);
    else if(cmd == "WORRY")
      worry(queue, iArg);
    else if(cmd == "QUIET")
      quiet(queue, iArg);
  }
  return 0;
}
