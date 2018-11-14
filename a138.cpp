#include <iostream>
#include <string>

using namespace std;

/**
Определите тип Incognizable, для которого следующий код будет корректен:
 * 
 */

class Incognizable 
{
public:
  Incognizable() {}
  Incognizable(int a) : _a(a) {}
  Incognizable(int a, int b) : _a(a), _b(b) {}
    
private:
  int _a = 0;
  int _b = 0;
};
/*
int main() 
{
  Incognizable a;
  Incognizable b = {};
  Incognizable c = {0};
  Incognizable d = {0, 1};
  return 0;
}
*/
