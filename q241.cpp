#include <iostream>
#include <set>
#include <vector>
#include <algorithm>


using namespace std;

bool f(int i)
{
  return (i%2) == 0;
}

void print(const char *msg, const vector<int> &v)
{
    cout << msg;
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

int main() 
{
  set<int> s = { 1,2,3,4,5,6,7,8,9,0 };
  vector<int> v;

  // Отметьте отрывки кода, которые заполнят вектор v всеми элементами множества s, не удовлетворяющими условию f.
{
    vector <int> garbage;
    partition_copy(
        begin(s), end(s),
        back_inserter(v), back_inserter(garbage), f);
    print("1: ", v); v.resize(0);
}
{
    vector<int> garbage;
    partition_copy(
        begin(s), end(s),
        back_inserter(garbage), back_inserter(v), f);  
  print("2: ", v); v.resize(0);
}
{
  remove_copy_if(begin(s), end(s), back_inserter(v), f);
  print("3: ", v); v.resize(0);
}
{
    v.assign(begin(s), end(s));
auto it = remove_if(begin(v), end(v),
                    [](int x) { return !f(x); });
v.erase(it, end(v));
  print("4: ", v); v.resize(0);
}
{
    /*
    auto it = remove_if(begin(s), end(s),
                    [](int x) { return !f(x); });
copy(it, end(s), back_inserter(v));
  print("5: ", v); v.resize(0);*/
}
{
    v.assign(begin(s), end(s));
    auto it = partition(begin(v), end(v), f);
    v.erase(begin(v), it);
  print("6: ", v); v.resize(0);
}
{
    copy_if(begin(s), end(s), back_inserter(v),
        [](int x) { return !f(x); });
  print("7: ", v); v.resize(0);
}
{
    remove_copy_if(begin(s), end(s), back_inserter(v),
               [](int x) { return !f(x); });
  print("8: ", v); v.resize(0);
}
{
    v.assign(begin(s), end(s));
    auto it = remove_if(begin(v), end(v), f);
    v.erase(it, end(v));
  print("9: ", v); v.resize(0);
}
{
   v.assign(begin(s), end(s));
    sort(begin(v), end(v),
        [](int lhs, int rhs) { return f(lhs) > f(rhs); });
    auto it = partition_point(begin(v), end(v), f);
    v.erase(begin(v), it);
  print("10: ", v); v.resize(0);
}
{
    v.assign(begin(s), end(s));
    auto it = partition(begin(v), end(v), f);
    v.erase(it, end(v));
    print("11: ", v); v.resize(0);
}
{
    v.assign(begin(s), end(s));
    sort(begin(v), end(v),
        [](int lhs, int rhs) { return f(lhs) > f(rhs); });
    auto it = partition_point(begin(v), end(v), f);
    v.erase(it, end(v));
  print("12: ", v); v.resize(0);
}
{  
  copy_if(begin(s), end(s), back_inserter(v), f);
  print("13: ", v); v.resize(0);
}
{/*
    auto it = partition(begin(s), end(s), f);
    copy(it, end(s), back_inserter(v));
    print("14: ", v); v.resize(0);*/
}

  return 0;
}
