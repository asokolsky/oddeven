#include <iostream>
using namespace std;

int main()
{
    unsigned int a, b;
    cin >> a >> b;
    if(b == 0)
    {
        cout << "Impossible" << endl;
        return 0;
    }
    unsigned int iRes = 0;
    for(;a >= (b * (iRes + 1)); iRes++)
        ;
    cout << iRes << endl;
    return 0;
}
