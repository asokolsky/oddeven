#include <iostream>
#include <map>
#include <string>


using namespace std;

/**
 * 
 */

int main()
{
  map<int, string> m = {{1, "odd"}, {2, "even"}, {1, "one"}};
  m[2] = "two";
  m.erase(1);
  m[3] = "three";
  m.erase(4);
  m[5] = "five";
  cout << m.size();  
  return 0;
}
