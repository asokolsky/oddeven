#include <iostream>
using namespace std;

int main()
{
    // n - original price
    //
    float n, a, b, x, y;
    cin >> n >> a >> b >> x >> y;
    float z;

    if(n > b)
      z = n - (n*y)/100;
    else if(n > a)
      z = n - (n*x)/100;
    else
      z = n;

    cout << z << endl;
    return 0;
}
